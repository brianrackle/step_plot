#ifndef PROJECT_STEP_LOG_H
#define PROJECT_STEP_LOG_H

#include <string>
#include <vector>
#include <functional>
#include "cereal/archives/json.hpp"
#include "format.h"

namespace step_log
{
    constexpr size_t x = 0, y = 1, z = 2;

//    enum class enum_geometry
//    {
//        e_point = 0,
//        e_line,
//        e_polygon
//    };
//
//    enum class enum_numeric
//    {
//        e_int8 = 0,
//        e_int16,
//        e_int32,
//        e_int64,
//        e_uint8,
//        e_uint16,
//        e_uint32,
//        e_uint64,
//        e_float32,
//        e_float64
//    };
//
//    enum class enum_dimension
//    {
//        e_1d = 0,
//        e_2d,
//        e_3d,
//        e_4d
//    };

    //TODO(brian): plots seperated by an 'e'(implicit indexing), or "\n\n"(explicit indexing)
    //segments should be seperated by a single newline, polyline/polygon no seperation
    //ploting with '-' file means all plots repeated for each explicit index
    //or data listed in order with implicit indexing ('e' seperators)
    //gnuplot 5 supports $VAR << EOD with indexing into data
    template<class NumericT, size_t Dimension>
    using vertex = std::array<NumericT, Dimension>;

    template <class StreamT, class NumericT, typename std::enable_if<std::is_integral<NumericT>::value>::type * = nullptr>
    void write(StreamT & stream, const NumericT & t_num)
    {
        stream.write("{:-d}", t_num);
    }

    template <class StreamT, class NumericT, typename std::enable_if<std::is_floating_point<NumericT>::value>::type * = nullptr>
    void write(StreamT & stream, const NumericT & t_num)
    {
        stream.write("{:-.16f}", t_num);
    }

    template <class StreamT, class VertexT, size_t Count> class write_helper;

    template <class StreamT, class VertexT>
    struct write_helper<StreamT, VertexT, 1>
    {
        void operator()(StreamT & stream, const VertexT & t_vertex)
        {
            write(stream, t_vertex[0]);
        }
    };

    template <class StreamT, class VertexT, size_t Count>
    struct write_helper : write_helper<StreamT, VertexT, Count - 1>
    {
        void operator()(StreamT & stream, const VertexT & t_vertex)
        {
            constexpr auto count_m = Count - 1;
            write_helper<StreamT, VertexT, count_m>()(stream, t_vertex);
            stream << ' ';
            write(stream, t_vertex[count_m]);
        }
    };

    template<class StreamT, class NumericT, size_t Dimension>
    void write(StreamT & stream, const vertex<NumericT, Dimension> & t_vertex)
    {
        using vertex_t = std::remove_cv_t<std::remove_reference_t<decltype(t_vertex)>>;
        write_helper<StreamT, vertex_t, Dimension>()(stream, t_vertex);
        stream << '\n';
    }

    template<class NumericT, size_t Dimension>
    struct point {
        using data_t = vertex<NumericT, Dimension>;
        using numeric_t = NumericT;
        using dimension_t = std::tuple_size<data_t>;

        template <class StreamT>
        void write(StreamT & stream) const
        {
            step_log::write(stream, data);
        }

        data_t data;
    };

    template<class NumericT, size_t Dimension>
    struct line {
        using data_t = std::array<vertex<NumericT, Dimension>, 2>;
        using numeric_t = NumericT;
        using dimension_t = std::tuple_size<data_t>;

        template <class StreamT>
        void write(StreamT & stream) const
        {
            step_log::write(stream, data[0]);
            step_log::write(stream, data[1]);
        }

        data_t data;
    };

//    template<class NumericT, size_t Dimension>
//    struct polygon {
//        using data_t = std::vector<vertex<NumericT, Dimension>>;
//        using numeric_t = NumericT;
//        using dimension_t = std::tuple_size<data_t>;
//
////        polygon() { }
////        polygon(data_t &&d) : data(std::move(d)) { }
//
//        data_t data;
//    };

    struct plot_base
    {
        virtual void unknown() = 0;
    };

    template <class GeometryT>
    struct plot : public plot_base
    {
        using data_t = std::vector<GeometryT>;
        using geometry_t = GeometryT;
        using numeric_t = typename GeometryT::numeric_t;
        using dimension_t = typename GeometryT::dimension_t;

        template <class StreamT>
        void write(StreamT & stream) const
        {
            for(const auto & d : data)
            {
                d.write(stream);
            }
            stream << '\n';
            stream << '\n';
        }

        virtual void unknown(){ }

        data_t data;
    };

    struct plots {
        using data_t = std::vector<std::unique_ptr<plot_base>>;
        using writer_t = fmt::MemoryWriter;

        data_t data;
        writer_t plot_stream;
//        //TODO(brian): access should be similarly templated
//        //TODO(brian): create a way for a passed template to execute. template specialization with function operator overload, passed iterator/pointer to plot
//        template <class NumericT, size_t Dimension>
//        data_t::iterator add(const enum_geometry & t_geometry)
//        {
//            switch(t_geometry) {
//                case enum_geometry::e_point:
//                    data.emplace_back(std::make_unique<plot<point<NumericT, Dimension>>>());
//                    return --data.end();
//                case enum_geometry::e_line:
//                    data.emplace_back(std::make_unique<plot<line<NumericT, Dimension>>>());
//                    return --data.end();
//                case enum_geometry::e_polygon:
//                    data.emplace_back(std::make_unique<plot<polygon<NumericT, Dimension>>>());
//                    return --data.end();
//            }
//        }
//
//        template <size_t Dimension>
//        data_t::iterator add(const enum_geometry & t_geometry, const enum_numeric & t_numeric)
//        {
//            switch(t_numeric) {
//                case enum_numeric::e_int8:
//                    return add<int8_t, Dimension>(t_geometry);
//                case enum_numeric::e_int16:
//                    return add<int16_t, Dimension>(t_geometry);
//                case enum_numeric::e_int32:
//                    return add<int32_t, Dimension>(t_geometry);
//                case enum_numeric::e_int64:
//                    return add<int64_t, Dimension>(t_geometry);
//                case enum_numeric::e_uint8:
//                    return add<uint8_t, Dimension>(t_geometry);
//                case enum_numeric::e_uint16:
//                    return add<uint16_t, Dimension>(t_geometry);
//                case enum_numeric::e_uint32:
//                    return add<uint32_t, Dimension>(t_geometry);
//                case enum_numeric::e_uint64:
//                    return add<uint64_t, Dimension>(t_geometry);
//                case enum_numeric::e_float32:
//                    return add<float, Dimension>(t_geometry);
//                case enum_numeric::e_float64:
//                    return add<double, Dimension>(t_geometry);
//            }
//        }
//
//        data_t::iterator add(const enum_geometry & t_geometry, const enum_numeric & t_numeric, const enum_dimension & t_dimension) {
//            switch (t_dimension) {
//                case enum_dimension::e_1d:
//                    return add<1>(t_geometry, t_numeric);
//                case enum_dimension::e_2d:
//                    return add<2>(t_geometry, t_numeric);
//                case enum_dimension::e_3d:
//                    return add<3>(t_geometry, t_numeric);
//                case enum_dimension::e_4d:
//                    return add<4>(t_geometry, t_numeric);
//            }
//        }

    };
}

#endif //PROJECT_STEP_LOG_H
