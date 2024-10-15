#pragma once
#include <functional>

namespace numerical_derivatives {

double first_derivative_left(const std::function<double(double)>& f, double x, double h);
double first_derivative_right(const std::function<double(double)>& f, double x, double h);
double first_derivative_central(const std::function<double(double)>& f, double x, double h);
double first_derivative_asymmetric(const std::function<double(double)>& f, double x, double h);
double second_derivative_central_2nd(const std::function<double(double)>& f, double x, double h);
double second_derivative_central_4th(const std::function<double(double)>& f, double x, double h);
double first_derivative_4th(const std::function<double(double)>& f, double x, double h);

}
