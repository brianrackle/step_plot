#include "step_log.h"

int main(int argc, char **argv) {
    using namespace k_dimensional;

    k3d<double> point0(1, 2, 3); //type xd<3, double>
    auto point1 = make_kd<double>(1, 2, 3); //type xd<3,double>
    auto point2 = make_kd(1, 2, 3); //type xd<3,int>

    kd<3, double> point3; //values are default constructed
    kd<3, double> point4(double { }, double{}, double{}); //values are default constructed
    auto v = get<0>(point4);
    {
        using namespace euclidian;
        auto value0 = get<x>(point0); //value0 == 1
        auto value1 = get<y>(point0); //value1 == 2
        auto value2 = get<z>(point0); //value2 == 3
    }
    {
        using namespace rgb;
        kd<3, unsigned char> color(255, 255, 255);
        auto value0 = get<r>(color);
        auto value1 = get<g>(color);
        auto value2 = get<b>(color);
        //TODO(brian): assert get<N>(xd(K)) N <= K
    }

//    for(std::size_t i = 0; i < 1000000; ++i)
//    {
//        std::size_t result = 0;
//        k3d<std::size_t> test(i, i + 1, i + 2);
//        static_for<0,size(test)>
//            (test,[](kd_element<std::size_t> v)
//            {
//                auto j = v;
//            });
//    }

}