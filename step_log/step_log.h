#ifndef PROJECT_STEP_LOG_H
#define PROJECT_STEP_LOG_H

#include <vector>
#include <cereal/archives/portable_binary.hpp>

//TODO(brian): finish plot definitions
using d_t = std::size_t;

template<d_t Dimension, class T>
class point_xd;

template<class T>
class point_xd<1, T> {
public:
    point_xd() { }

    point_xd(const T &v) : value(v) { }

    T value = {};
};

template<d_t Dimension, class T>
class point_xd {
public:
    point_xd() { }

    template<class ... Ts>
    point_xd(const T &v, const Ts &... vs) : value(v), tail(vs...) { }

    T value = {};
    point_xd<Dimension - 1, T> tail;
};

template<class T, class ... Ts>
auto make_point_xd(const T &v, const Ts &... vs) {
    return point_xd<1 + sizeof...(vs), T>(v, vs...);
}

template<d_t D, d_t Dimension, class T>
class get_helper;

template<d_t Dimension, class T>
class get_helper<0, Dimension, T> {
public:
    auto &operator()(const point_xd<Dimension, T> &v) {
        return v.value;
    }
};

template<d_t D, d_t Dimension, class T>
class get_helper {
public:
    auto &operator()(const point_xd<Dimension, T> &v) {
        get_helper<D - 1, Dimension - 1, T> helper;
        return helper(v.tail);
    }
};

template<d_t D, d_t Dimension, class T>
auto &get(const point_xd<Dimension, T> &v) {
    get_helper<D, Dimension, T> helper;
    return helper(v);
}

template<d_t Dimension, class T>
class primitive {
    std::vector<point_xd<Dimension, T>> data;
};

//template <class T>
//class points : public primitive
//{
//public:
//
//};
//
//template <class T>
//class line : public points
//{
//
//};
//
//template <class T>
//class polygon : public points
//{
//
//};

template<class T>
class plot {
    //need format for grouping during output
    // std::vector<primitive<T>> data;
};

//TODO(brian): verify T is a numeric type
template<class T>
class plots {
    // std::vector<plot<T>> data;
};

#endif //PROJECT_STEP_LOG_H
