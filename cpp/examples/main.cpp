#include "numerical_derivatives/derivatives.hpp"
#include "numerical_derivatives/utils.hpp"
#include "numerical_derivatives/plotting.hpp"
#include <iostream>
#include <cmath>

int main() {
    std::cout << "Numerical Derivatives Example\n";

    auto f = [](double x) { return std::sin(x); };
    double x = M_PI / 4;
    double h = 0.5;

    numerical_derivatives::plot_derivatives_comparison(numerical_derivatives::func, -5, 5, 0.01, "central", 30);
    numerical_derivatives::plot_derivatives_comparison(numerical_derivatives::func, -5, 5, 0.01, "4th_order", 30);

    return 0;
}
