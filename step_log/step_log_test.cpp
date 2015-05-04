#include <iostream>
#include "step_log.h"

int main(int argc, char **argv) {
    using namespace step_log;

 //   plots test;
//    auto plot = test.add(enum_geometry::e_line, enum_numeric::e_float64, enum_dimension::e_2d);
    //plot

    fmt::MemoryWriter out;


    vertex<double, 3> p0 = {100000.12345678, 1, 2};
    write(out, p0);
    std::cout << out.c_str() << std::endl;
    //td::cout << p0.to_string() << std::endl;

    //out.write
}