#include "step_log.h"

int main(int argc, char **argv) {
    using namespace step_log;

    using plots_t = plots <point<double, 2>, line<double, 2>, line<double, 2>>;

    plots_t ps;
    plots_t::group_t group;

    //TODO(brian):work on access to model how deserialization will work
    //TODO(brian):work on access to model how creation/serialization will work
//    for(size_t i = 0; i < plots_t::stride::value; ++i)
//    {
//        std::get<i>plots_t::group_n_t<i> p;
//    }
    //using plot_t = plot<point<double, 2>>;

    // plots_t ps;
    //ps.


//    plot_t p;
//    p.data.push_back({{0,0}});


    //plot groups can just be organized by stride

}