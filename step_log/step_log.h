#ifndef PROJECT_STEP_LOG_H
#define PROJECT_STEP_LOG_H

#include <vector>
#include "cereal/archives/json.hpp"

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

    struct plots {
        using data_t = std::vector<std::unique_ptr<plot_base>>;

        data_t data;

        template <class NumericT, size_t Dimension>
        std::unique_ptr<plot_base> AddPlot(const enum_geometry & t_geometry)
        {
            switch(t_geometry) {
                case enum_geometry::e_point:
                    return std::make_unique<plot<point<NumericT, Dimension>>>();
                case enum_geometry::e_line:
                    return std::make_unique<plot<line<NumericT, Dimension>>>();
                case enum_geometry::e_polygon:
                    return std::make_unique<plot<polygon<NumericT, Dimension>>>();
            }
        }

        template <size_t Dimension>
        std::unique_ptr<plot_base> AddPlot(const enum_geometry & t_geometry, const enum_numeric & t_numeric)
        {
            switch(t_numeric) {
                case enum_numeric::e_int8:
                    return AddPlot<int8_t, Dimension>(t_geometry);
                case enum_numeric::e_int16:
                    return AddPlot<int16_t, Dimension>(t_geometry);
                case enum_numeric::e_int32:
                    return AddPlot<int32_t, Dimension>(t_geometry);
                case enum_numeric::e_int64:
                    return AddPlot<int64_t, Dimension>(t_geometry);
                case enum_numeric::e_uint8:
                    return AddPlot<uint8_t, Dimension>(t_geometry);
                case enum_numeric::e_uint16:
                    return AddPlot<uint16_t, Dimension>(t_geometry);
                case enum_numeric::e_uint32:
                    return AddPlot<uint32_t, Dimension>(t_geometry);
                case enum_numeric::e_uint64:
                    return AddPlot<uint64_t, Dimension>(t_geometry);
                case enum_numeric::e_float32:
                    return AddPlot<float, Dimension>(t_geometry);
                case enum_numeric::e_float64:
                    return AddPlot<double, Dimension>(t_geometry);
            }
        }

        std::unique_ptr<plot_base> AddPlot(const enum_geometry & t_geometry, const enum_numeric & t_numeric, const enum_dimension & t_dimension) {
            switch (t_dimension) {
                case enum_dimension::e_1d:
                    return AddPlot<1>(t_geometry, t_numeric);
                case enum_dimension::e_2d:
                    return AddPlot<2>(t_geometry, t_numeric);
                case enum_dimension::e_3d:
                    return AddPlot<3>(t_geometry, t_numeric);
                case enum_dimension::e_4d:
                    return AddPlot<4>(t_geometry, t_numeric);
            }
        }

    };
}

#endif //PROJECT_STEP_LOG_H
