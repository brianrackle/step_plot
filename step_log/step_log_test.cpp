#include <iostream>
#include "step_log.h"

int main(int argc, char **argv) {
    using namespace step_log;

 //   plots test;
//    auto plot = test.add(enum_geometry::e_line, enum_numeric::e_float64, enum_dimension::e_2d);
    //plot

    fmt::MemoryWriter p_out;
    point<double, 3> p0 = {100000.12345678, 1, 2};
    p0.write(p_out);
    std::cout << p_out.c_str() << std::endl;

    fmt::MemoryWriter l_out;
    line<double, 2> l0 = {{{ {0, 1}, {2, 3} }}};
    l0.write(l_out);
    std::cout << l_out.c_str() << std::endl;

    fmt::MemoryWriter pl_out;
    plot<point<double, 2>> pl0;
    pl0.data = {{1,2}, {3, 4}, {5, 6}};
    pl0.write(pl_out);
    std::cout << pl_out.c_str() << std::endl;

    //out.write
}