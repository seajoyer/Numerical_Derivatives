import matplotlib.pyplot as plt
import numpy as np
from numerical_derivatives import (
    first_derivative_left,
    first_derivative_right,
    first_derivative_central,
    first_derivative_asymmetric,
    second_derivative_central_2nd_accuracy,
    second_derivative_central_4th_accuracy,
    plot_derivatives_comparison,
)
from numerical_derivatives.utils import (
    f,
    f_1st_derivative,
    f_2nd_derivative,
    generate_grid,
)

a = -5
b =  5
h_min = 0.000001
h_max = 0.00001
h_step = 0.000004

h_range = np.arange(h_min, h_max, h_step)

ln_error = []
ln_h = []

for h in h_range:
    x = generate_grid(a, b, h)

    numerical_derivative  = [first_derivative_central(f, xi, h) for xi in x]
    analytical_derivative = f_1st_derivative(x)

    max_error = max(np.abs(np.array(numerical_derivative) - analytical_derivative))
    ln_error.append(np.log(max_error))
    ln_h.append(np.log(h))

print(np.exp(ln_h[ln_error.index(min(ln_error))]))

plt.figure(figsize=(12, 8))
plt.xlabel('ln(h)', fontsize=16)
plt.ylabel('ln(max_error)', fontsize=16)
plt.plot(ln_h, ln_error, label='Numerical Derivative Errors', linewidth=2.0)
plt.scatter(ln_h, ln_error, color = "red")
plt.grid(True)
plt.show()
