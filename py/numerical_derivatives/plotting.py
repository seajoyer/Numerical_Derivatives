import numpy as np
import matplotlib.pyplot as plt
from .utils import generate_grid

def plot_derivatives_comparison(f, f_analyt_der, f_numeric_der, x_range, h):
    x = generate_grid(x_range[0], x_range[1], h)

    numerical_derivative  = [f_numeric_der(f, xi, h) for xi in x]
    analytical_derivative = f_analyt_der(x)

    error = np.abs(np.array(numerical_derivative) - analytical_derivative)

    plt.figure(figsize=(12, 8))
    plt.plot(x, numerical_derivative, label='Numerical Derivative')
    plt.plot(x, analytical_derivative, label='Analytical Derivative')
    plt.plot(x, error, label='Absolute Error')
    plt.xlabel('x')
    plt.ylabel('y')
    # plt.title(f'Derivative Comparison ({method} method)')
    plt.legend()
    plt.grid(True)
    plt.show()
