#pragma once
#include <string>
#include <functional>

namespace numerical_derivatives {

void plot_derivatives_comparison(
    const std::function<double(double)>& f,
    double x_min, double x_max,
    double h,
    const std::string& method = "central",
    std::size_t grid_step = 100
);

}
