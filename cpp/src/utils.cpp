#include "numerical_derivatives/utils.hpp"
#include <cmath>

namespace numerical_derivatives {

std::vector<double> generate_grid(double a, double b, int n) {
    std::vector<double> grid(n);
    double step = (b - a) / (n - 1);
    for (int i = 0; i < n; ++i) {
        grid[i] = a + i * step;
    }
    return grid;
}

double func(double x) {
    return std::cosh(std::exp(-x * x));
}

double analytical_first_derivative(double x) {
    return -2 * x * std::exp(-x * x) * std::sinh(std::exp(-x * x));
}

}
