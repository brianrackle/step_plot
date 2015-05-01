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

    struct geometry
    {

    };

    template<class NumericT, size_t Dimension>
    struct point : public geometry {
        using data_t = vertex<NumericT, Dimension>;

        point() { }

        point(data_t &&d) : data(std::move(d)) { }

        data_t data;
    };

    template<class NumericT, size_t Dimension>
    struct line : public geometry {
        using data_t = std::array<vertex<NumericT, Dimension>, 2>;

        line() { }

        line(data_t &&d) : data(std::move(d)) { }

        data_t data;
    };

    template<class NumericT, size_t Dimension>
    struct polygon : public geometry {
        using data_t = std::vector<vertex<NumericT, Dimension>>;

        polygon() { }

        polygon(data_t &&d) : data(std::move(d)) { }

        data_t data;
    };

    //A collection of a single geometry type that serves as a plot.
    template <class Geometry, class NumericT, size_t Dimension>
    struct plot <Geometry<NumericT, Dimension>> {
        using geometry_t = Geometry;
        using data_t = std::vector<geometry_t>; //limit plot to having only a single geometry type

        plot() { }

        plot(data_t &&d) : data(std::move(d)) { }

        data_t data;
    };

//    struct plots {
//        using data_t = std::vector<std::unique_ptr<geometry>>;
//
//
//        plots
////        plots() { }
////
////        plots(data_t &&d) : data(std::move(d)) { }
////
//        data_t data;
//
//        template <class NumericT, size_t Dimension>
//        std::unique_ptr<plot<geometry>> AddPlot(const enum_geometry & t_geometry)
//        {
//            switch(t_geometry) {
//                case enum_geometry::e_point:
//                    return std::make_unique<plot<point<NumericT, Dimension>>>();
//                case enum_geometry::e_line:
//                    return std::make_unique<plot<line<NumericT, Dimension>>>();
//                case enum_geometry::e_polygon:
//                    return std::make_unique<plot<polygon<NumericT, Dimension>>>();
//            }
//        }
//
//        template <size_t Dimension>
//        std::unique_ptr<geometry> AddPlot(const enum_geometry & t_geometry, const enum_numeric & t_numeric)
//        {
//            switch(t_numeric) {
//                case enum_numeric::e_int8:
//                    return AddPlot<Dimension,int8_t>(t_geometry);
//                case enum_numeric::e_int16:
//                    return AddPlot<Dimension,int16_t>(t_geometry);
//                case enum_numeric::e_int32:
//                    return AddPlot<Dimension,int32_t>(t_geometry);
//                case enum_numeric::e_int64:
//                    return AddPlot<Dimension,int64_t>(t_geometry);
//                case enum_numeric::e_uint8:
//                    return AddPlot<Dimension,uint8_t>(t_geometry);
//                case enum_numeric::e_uint16:
//                    return AddPlot<Dimension,uint16_t>(t_geometry);
//                case enum_numeric::e_uint32:
//                    return AddPlot<Dimension,uint32_t>(t_geometry);
//                case enum_numeric::e_uint64:
//                    return AddPlot<Dimension,uint64_t>(t_geometry);
//                case enum_numeric::e_float32:
//                    return AddPlot<Dimension,float>(t_geometry);
//                case enum_numeric::e_float64:
//                    return AddPlot<Dimension,double>(t_geometry);
//            }
//        }
//
//        std::unique_ptr<geometry> AddPlot(const enum_geometry & t_geometry, const enum_numeric & t_numeric, const enum_dimension & t_dimension)
//        {
//            switch(t_dimension) {
//                case enum_dimension::e_1d:
//                    return AddPlot<1>(t_geometry, t_numeric);
//                case enum_dimension::e_2d:
//                    return AddPlot<2>(t_geometry, t_numeric);
//                case enum_dimension::e_3d:
//                    return AddPlot<3>(t_geometry, t_numeric);
//                case enum_dimension::e_4d:
//                    return AddPlot<4>(t_geometry, t_numeric);
//            }
//
//    };
}

#endif //PROJECT_STEP_LOG_H
