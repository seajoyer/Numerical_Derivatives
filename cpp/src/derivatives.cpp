#include "numerical_derivatives/derivatives.hpp"
#include <cmath>

namespace numerical_derivatives {

double first_derivative_left(const std::function<double(double)>& f, double x, double h) {
    return (f(x) - f(x - h)) / h;
}

double first_derivative_right(const std::function<double(double)>& f, double x, double h) {
    return (f(x + h) - f(x)) / h;
}

double first_derivative_central(const std::function<double(double)>& f, double x, double h) {
    return (f(x + h) - f(x - h)) / (2 * h);
}

double first_derivative_asymmetric(const std::function<double(double)>& f, double x, double h) {
    return (-3 * f(x) + 4 * f(x + h) - f(x + 2 * h)) / (2 * h);
}

double second_derivative_central_2nd(const std::function<double(double)>& f, double x, double h) {
    return (f(x + h) - 2 * f(x) + f(x - h)) / (h * h);
}

double second_derivative_central_4th(const std::function<double(double)>& f, double x, double h) {
    return (-f(x + 2*h) + 16*f(x + h) - 30*f(x) + 16*f(x - h) - f(x - 2*h)) / (12 * h * h);
}

double first_derivative_4th(const std::function<double(double)>& f, double x, double h) {
    return (-f(x + 2*h) + 8*f(x + h) - 8*f(x - h) + f(x - 2*h)) / (12 * h);
}

}
