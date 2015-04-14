#ifndef PROJECT_STEP_LOG_H
#define PROJECT_STEP_LOG_H

#include <vector>
#include <cereal/archives/portable_binary.hpp>

namespace x_dimensional {
    using d_t = std::size_t;

    namespace euclidian {
        constexpr d_t x = 0, y = 1, z = 2;
    }

    namespace homogenous {
        constexpr d_t x = 0, y = 1, z = 2, w = 3;
    }

    namespace rgba {
        constexpr d_t r = 0, g = 1, b = 2, a = 3;
    }

    namespace cymk {
        constexpr d_t c = 0, y = 1, m = 2, k = 3;
    }

    template<d_t Dimension, class T>
    class xd;

    template<class T>
    class xd<1, T> {
    public:
        xd() { }

        xd(const T &v) : value(v) { }

        T value = {};
    };

    template<d_t Dimension, class T>
    class xd {
    public:
        xd() { }

        template<class ... Ts>
        xd(const T &v, const Ts &... vs) : value(v), tail(vs...) { }

        T value = {};
        xd<Dimension - 1, T> tail;
    };

    template<class T, class ... Ts>
    auto make_point_xd(const T &v, const Ts &... vs) {
        return xd<1 + sizeof...(vs), T>(v, vs...);
    }

    template<d_t D, d_t Dimension, class T>
    class get_helper;

    template<d_t Dimension, class T>
    class get_helper<0, Dimension, T> {
    public:
        auto &operator()(const xd<Dimension, T> &v) {
            return v.value;
        }
    };

    template<d_t D, d_t Dimension, class T>
    class get_helper {
    public:
        auto &operator()(const xd<Dimension, T> &v) {
            get_helper<D - 1, Dimension - 1, T> helper;
            return helper(v.tail);
        }
    };

    template<d_t D, d_t Dimension, class T>
    auto &get(const xd<Dimension, T> &v) {
        get_helper<D, Dimension, T> helper;
        return helper(v);
    }

    template<d_t Dimension, class T>
    class primitive {
        std::vector<xd<Dimension, T>> data;
    };
}

//TODO(brian): finish plot definitions

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
