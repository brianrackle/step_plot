#ifndef PROJECT_STEP_LOG_H
#define PROJECT_STEP_LOG_H

#include <vector>
#include <cereal/archives/portable_binary.hpp>

//TODO(brian): allow for matrix definitions up to hypermatrix
namespace k_dimensional {
    using dimension_t = std::size_t;

    template<class Type>
    using kd_element = Type &;

    template<dimension_t Dimension, class Type>
    class kd;

    template<class Type>
    class kd<1, Type> {
    public:
        kd() { }

        kd(const Type &v) : value(v) { }

    private:
        template<dimension_t I, dimension_t D, class T>
        friend
        class get_helper;

        Type value = {};
    };

    template<dimension_t Dimension, class Type>
    class kd {
    public:
        kd() { }

        template<class ... Ts>
        kd(const Type &v, const Ts &... vs) : value(v), tail(vs...) { }

    private:
        template<dimension_t I, dimension_t D, class T>
        friend
        class get_helper;

        Type value = {};
        kd<Dimension - 1, Type> tail;
    };

    //TODO(brian): complete perfect forwarding
    //TODO(brian): complete r-value reference passing
    template<class Type, class ... Ts>
    auto make_kd(const Type &&v, const Ts &&... vs) {
        return kd<1 + sizeof...(vs), Type>(v, vs...);
    }

    template<dimension_t Index, dimension_t Dimension, class Type>
    class get_helper;

    template<dimension_t Dimension, class Type>
    class get_helper<0, Dimension, Type> {
    public:
        constexpr kd_element<Type> operator()(const kd<Dimension, Type> &v) {
            return const_cast<Type &>(v.value);
        }
    };

    template<dimension_t Index, dimension_t Dimension, class Type>
    class get_helper {
    public:
        constexpr kd_element<Type> operator()(const kd<Dimension, Type> &v) {
            return get_helper<Index - 1, Dimension - 1, Type>()(v.tail);
        }
    };

    template<dimension_t Index, dimension_t Dimension, class Type>
    constexpr kd_element<Type> get(const kd<Dimension, Type> &v) {
        return get_helper<Index, Dimension, Type>()(v);
    }

    template<dimension_t Dimension, class Type>
    constexpr dimension_t size(const kd<Dimension, Type> &v) {
        return Dimension;
    }

//    template<dimension_t FromIndex, dimension_t ToIndex, dimension_t Dimension, class Type>
//    class static_for_helper;
//
//    template<dimension_t ToIndex, dimension_t Dimension, class Type>
//    class static_for_helper<ToIndex, ToIndex, Dimension, Type>
//    {
//        void operator()(const kd<Dimension, Type> &v, const std::function<void (kd_element<Type>)> & func)
//        {
//
//        }
//    };
//
//    template<dimension_t FromIndex, dimension_t ToIndex, dimension_t Dimension, class Type>
//    class static_for_helper
//    {
//        void operator()(const kd<Dimension, Type> &v, const std::function<void (kd_element<Type>)> & func)
//        {
//            func(get<FromIndex>(v));
//            static_for_helper<FromIndex + 1, ToIndex, Dimension, Type>()(v, func);
//        }
//    };

//    template<dimension_t FromIndex, dimension_t ToIndex, dimension_t Dimension, class Type>
//    void static_for(const kd<Dimension, Type> &v, std::function<void (kd_element<Type>)> func)
//    {
//        //static_for_helper<FromIndex, ToIndex, Dimension, Type>()(v, func);
//    }

    //TODO(brian): add other common dimensional types under relevant namespaces
    template<class Type>
    using k1d = kd<1, Type>;
    template<class Type>
    using k2d = kd<2, Type>;
    template<class Type>
    using k3d = kd<3, Type>;
    template<class Type>
    using k4d = kd<4, Type>;

    namespace euclidian {
        constexpr dimension_t x = 0, y = 1, z = 2;
    }

    namespace homogenous {
        constexpr dimension_t x = 0, y = 1, z = 2, w = 3;
    }

    namespace rgb {
        constexpr dimension_t r = 0, g = 1, b = 2;
    }

    namespace cmyk {
        constexpr dimension_t c = 0, m = 1, y = 2, k = 3;
    }
}

//template<dimension_t Dimension, class Type>
//class primitive {
//    std::vector<kd<Dimension, Type>> data;
//};
//TODO(brian): finish plot definitions

//template <class Type>
//class points : public primitive
//{
//public:
//
//};
//
//template <class Type>
//class line : public points
//{
//
//};
//
//template <class Type>
//class polygon : public points
//{
//
//};

template<class Type>
class plot {
    //need format for grouping during output
    // std::vector<primitive<Type>> data;
};

//TODO(brian): verify Type is a numeric type
template<class Type>
class plots {
    // std::vector<plot<Type>> data;
};

#endif //PROJECT_STEP_LOG_H
