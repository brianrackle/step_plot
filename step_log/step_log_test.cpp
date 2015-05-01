#include "step_log.h"

int main(int argc, char **argv) {
    using namespace step_log;

    plots test;
    auto plot = test.add(enum_geometry::e_line, enum_numeric::e_float64, enum_dimension::e_2d);

    //add should be a template that takes functions so code can be customized for point, line, polygon

}