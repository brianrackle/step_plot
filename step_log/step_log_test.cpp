#include "step_log.h"

int main(int argc, char **argv) {
    using namespace x_dimensional;

    xd<3, double> point0(1, 2, 3); //type xd<3, double>
    auto point1 = make_point_xd<double>(1, 2, 3); //type xd<3,double>
    auto point2 = make_point_xd(1, 2, 3); //type xd<3,int>
    xd<3, double> point3; //values are default constructed
    {
        using namespace euclidian;
        auto value0 = get<x>(point0); //value0 == 1
        auto value1 = get<y>(point0); //value1 == 2
        auto value2 = get<z>(point0); //value2 == 3
    }
    {
        using namespace rgba;
        auto value0 = get<r>(point0);
        auto value1 = get<g>(point1);
        auto value2 = get<b>(point2);
        //TODO(brian): assert get<N>(xd(K)) N <= K
    }

}