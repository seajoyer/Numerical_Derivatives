def first_derivative_left(f, x, h):
    return (f(x) - f(x - h)) / h

def first_derivative_right(f, x, h):
    return (f(x + h) - f(x)) / h

def first_derivative_central(f, x, h):
    return (f(x + h) - f(x - h)) / (2 * h)

def first_derivative_asymmetric(f, x, h):
    return (-3 * f(x) + 4 * f(x + h) - f(x + 2 * h)) / (2 * h)

def second_derivative_central_2nd_accuracy(f, x, h):
    return (f(x + h) - 2 * f(x) + f(x - h)) / (h ** 2)

def second_derivative_central_4th_accuracy(f, x, h):
    return (-f(x + 2*h) + 16*f(x + h) - 30*f(x) + 16*f(x - h) - f(x - 2*h)) / (12 * h ** 2)
