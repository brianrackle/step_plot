#include "step_log.h"

int main(int argc, char **argv) {
    //TODO(brian): put in namespace cartesian
    const d_t x = 0, y = 1, z = 2;

    point_xd<3, double> point0(1, 2, 3); //type point_xd<3, double>
    auto point1 = make_point_xd<double>(1, 2, 3); //type point_xd<3,double>
    auto point2 = make_point_xd(1, 2, 3); //type point_xd<3,int>
    point_xd<3, double> point3;
    auto value0 = get<x>(point0);
    auto value1 = get<y>(point0);
    auto value2 = get<z>(point0);
}