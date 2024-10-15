#include "numerical_derivatives/plotting.hpp"
#include "numerical_derivatives/derivatives.hpp"
#include "numerical_derivatives/utils.hpp"
#include <cstddef>
#include <cstdio>
#include <vector>
#include <stdexcept>

namespace numerical_derivatives {

void plot_derivatives_comparison(
    const std::function<double(double)>& f,
    double x_min, double x_max,
    double h,
    const std::string& method,
    std::size_t grid_step
) {
    std::vector<double> x = generate_grid(x_min, x_max, 20);
    std::vector<double> numerical_derivative(x.size());
    std::vector<double> analytical_derivative(x.size());
    std::vector<double> error(x.size());

    for (size_t i = 0; i < x.size(); ++i) {
        if (method == "central") {
            numerical_derivative[i] = first_derivative_central(f, x[i], h);
        } else if (method == "4th_order") {
            numerical_derivative[i] = first_derivative_4th(f, x[i], h);
        } else {
            throw std::invalid_argument("Method must be either 'central' or '4th_order'");
        }
        analytical_derivative[i] = analytical_first_derivative(x[i]);
        error[i] = std::abs(numerical_derivative[i] - analytical_derivative[i]);
    }

    FILE* gnuplot = popen("gnuplot -persistent", "w");
    if (!gnuplot) {
        throw std::runtime_error("Could not open gnuplot");
    }

    fprintf(gnuplot, "set title 'Derivative Comparison (%s method)'\n", method.c_str());
    fprintf(gnuplot, "set xlabel 'x'\n");
    fprintf(gnuplot, "set ylabel 'y'\n");
    fprintf(gnuplot, "plot '-' with lines lw 4 title 'Numerical Derivative', "
                     "'-' with lines lw 4 title 'Analytical Derivative', "
                     "'-' with lines lw 4 title 'Absolute Error'\n");

    for (size_t i = 0; i < x.size(); ++i) {
        fprintf(gnuplot, "%f %f\n", x[i], numerical_derivative[i]);
    }
    fprintf(gnuplot, "e\n");

    for (size_t i = 0; i < x.size(); ++i) {
        fprintf(gnuplot, "%f %f\n", x[i], analytical_derivative[i]);
    }
    fprintf(gnuplot, "e\n");

    for (size_t i = 0; i < x.size(); ++i) {
        fprintf(gnuplot, "%f %f\n", x[i], error[i]);
    }
    fprintf(gnuplot, "e\n");

    fflush(gnuplot);
    pclose(gnuplot);
}

}
