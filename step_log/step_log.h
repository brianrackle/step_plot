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

    enum class enum_geometry
    {
        e_point = 0,
        e_line,
        e_polygon
    };

    enum class enum_numeric
    {
        e_int8 = 0,
        e_int16,
        e_int32,
        e_int64,
        e_uint8,
        e_uint16,
        e_uint32,
        e_uint64,
        e_float32,
        e_float64
    };

    enum class enum_dimension
    {
        e_1d = 0,
        e_2d,
        e_3d,
        e_4d
    };

    template<class NumericT, size_t Dimension>
    using vertex = std::array<NumericT, Dimension>;

    template <class NumericT, typename std::enable_if<std::is_integral<NumericT>::value>::type * = nullptr>
    std::string to_string(const NumericT & t_num)
    {
        return fmt::format("{:-d}", t_num);
    }

    template <class NumericT, typename std::enable_if<std::is_floating_point<NumericT>::value>::type * = nullptr>
    std::string to_string(const NumericT & t_num)
    {
        return fmt::format("{:-.16f}", t_num);
    }

//    std::string to_string(const vertex & t_vertex)
//    {
//        return fmt::format("{}");
//    }

    //TODO(brian): plot might need to be specialized for each geometry for correct plot rendering
    //TODO(brian): create way to iterate points, add points, remove points


    template<class NumericT, size_t Dimension>
    struct point {
        using data_t = vertex<NumericT, Dimension>;
        using numeric_t = NumericT;
        using dimension_t = std::tuple_size<data_t>;

//        point() { }
//        point(data_t &&d) : data(std::move(d)) { }

        data_t data;
    };

    template<class NumericT, size_t Dimension>
    struct line {
        using data_t = std::array<vertex<NumericT, Dimension>, 2>;
        using numeric_t = NumericT;
        using dimension_t = std::tuple_size<data_t>;

//        line() { }
//        line(data_t &&d) : data(std::move(d)) { }

        data_t data;
    };

    template<class NumericT, size_t Dimension>
    struct polygon {
        using data_t = std::vector<vertex<NumericT, Dimension>>;
        using numeric_t = NumericT;
        using dimension_t = std::tuple_size<data_t>;

//        polygon() { }
//        polygon(data_t &&d) : data(std::move(d)) { }

        data_t data;
    };

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

        virtual void unknown(){ }

        data_t data;
    };

    //TODO(brian) logic for rendering a plot should be inside plot, then inside geometry
    struct plots {
        using data_t = std::vector<std::unique_ptr<plot_base>>;
        //TODO(brian): plots should store vector of enums
        data_t data;

        //TODO(brian): access should be similarly templated
        //TODO(brian): create a way for a passed template to execute. template specialization with function operator overload, passed iterator/pointer to plot
        template <class NumericT, size_t Dimension>
        data_t::iterator add(const enum_geometry & t_geometry)
        {
            switch(t_geometry) {
                case enum_geometry::e_point:
                    data.emplace_back(std::make_unique<plot<point<NumericT, Dimension>>>());
                    return --data.end();
                case enum_geometry::e_line:
                    data.emplace_back(std::make_unique<plot<line<NumericT, Dimension>>>());
                    return --data.end();
                case enum_geometry::e_polygon:
                    data.emplace_back(std::make_unique<plot<polygon<NumericT, Dimension>>>());
                    return --data.end();
            }
        }

        template <size_t Dimension>
        data_t::iterator add(const enum_geometry & t_geometry, const enum_numeric & t_numeric)
        {
            switch(t_numeric) {
                case enum_numeric::e_int8:
                    return add<int8_t, Dimension>(t_geometry);
                case enum_numeric::e_int16:
                    return add<int16_t, Dimension>(t_geometry);
                case enum_numeric::e_int32:
                    return add<int32_t, Dimension>(t_geometry);
                case enum_numeric::e_int64:
                    return add<int64_t, Dimension>(t_geometry);
                case enum_numeric::e_uint8:
                    return add<uint8_t, Dimension>(t_geometry);
                case enum_numeric::e_uint16:
                    return add<uint16_t, Dimension>(t_geometry);
                case enum_numeric::e_uint32:
                    return add<uint32_t, Dimension>(t_geometry);
                case enum_numeric::e_uint64:
                    return add<uint64_t, Dimension>(t_geometry);
                case enum_numeric::e_float32:
                    return add<float, Dimension>(t_geometry);
                case enum_numeric::e_float64:
                    return add<double, Dimension>(t_geometry);
            }
        }

        data_t::iterator add(const enum_geometry & t_geometry, const enum_numeric & t_numeric, const enum_dimension & t_dimension) {
            switch (t_dimension) {
                case enum_dimension::e_1d:
                    return add<1>(t_geometry, t_numeric);
                case enum_dimension::e_2d:
                    return add<2>(t_geometry, t_numeric);
                case enum_dimension::e_3d:
                    return add<3>(t_geometry, t_numeric);
                case enum_dimension::e_4d:
                    return add<4>(t_geometry, t_numeric);
            }
        }

    };
}

#endif //PROJECT_STEP_LOG_H
