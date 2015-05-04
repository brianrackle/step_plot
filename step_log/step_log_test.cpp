#include <iostream>
#include "step_log.h"

int main(int argc, char **argv) {
    using namespace step_log;

    plots test;
    auto plot = test.add(enum_geometry::e_line, enum_numeric::e_float64, enum_dimension::e_2d);
    //plot

    vertex<double, 3> v0 = {{100000.12345678, 1, 2}};

    std::cout << to_string(123456789) << std::endl;
    std::cout << to_string(100.1234567800000) << std::endl;
    std::cout << to_string(v0) << std::endl;
}