#ifndef PROJECT_STEP_LOG_H
#define PROJECT_STEP_LOG_H

#include <vector>
#include <cereal/archives/portable_binary.hpp>
#include <multi.hpp>

//TODO(brian): allow for matrix definitions up to hypermatrix
namespace step_log {

    constexpr size_t x = 0, y = 1, z = 2;

    template<class NumericT, size_t Dimension>
    using vertex = multi::array<NumericT, Dimension>;

    struct geometry {
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
    template<class GeometryType>
    struct plot {
        using geometry_t = GeometryType;
        using data_t = std::vector<GeometryType>; //limit plot to having only a single geometry type

        plot() { }

        plot(data_t &&d) : data(std::move(d)) { }

        data_t data;
    };

    //the order of the geometries should be defined, so use tuple instead
    template<class... GeometryType>
    struct plots {
        using group_t = std::tuple<plot<GeometryType>...>;
        template<size_t I>
        using group_n_t = typename std::tuple_element<I, group_t>::type;
        using stride = std::tuple_size<group_t>;
        using data_t = std::vector<group_t>;


        plots() { }

        plots(data_t &&d) : data(std::move(d)) { }

        data_t data;
    };
};

#endif //PROJECT_STEP_LOG_H
