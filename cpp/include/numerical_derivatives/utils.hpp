#pragma once
#include <vector>
#include <functional>

namespace numerical_derivatives {

std::vector<double> generate_grid(double a, double b, int n);
double func(double x);
double analytical_first_derivative(double x);

}
