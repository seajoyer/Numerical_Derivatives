import matplotlib.pyplot as plt
from tqdm import tqdm
import numpy as np
from concurrent.futures import ThreadPoolExecutor, as_completed
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

def calculate_error(h):
    x = generate_grid(a, b, h)
    numerical_derivative = first_derivative_central(f, x, h)
    analytical_derivative = f_1st_derivative(x)
    max_error = max(np.abs(np.array(numerical_derivative) - analytical_derivative))
    return h, np.log(max_error), np.log(h)

a = -5
b = 5
h_min  = 0.0000005
h_max  = 0.00002
h_step = 0.0000004

h_range = np.arange(h_min, h_max, h_step)

# Create a list to store results in order
results = [None] * len(h_range)

# Use ThreadPoolExecutor to parallelize the computation
with ThreadPoolExecutor() as executor:
    # Submit all tasks and store futures with their indices
    future_to_index = {executor.submit(calculate_error, h): i for i, h in enumerate(h_range)}

    # Process results as they complete
    for future in tqdm(as_completed(future_to_index), total=len(h_range)):
        index = future_to_index[future]
        results[index] = future.result()

# Unpack results in the correct order
ln_h = [result[2] for result in results]
ln_error = [result[1] for result in results]

# Find the h value that gives the minimum error
min_error_index = ln_error.index(min(ln_error))
min_error_h = np.exp(ln_h[min_error_index])
print(f"h value with minimum error: {min_error_h}")

plt.figure(figsize=(12, 8))
plt.xlabel('ln(h)', fontsize=16)
plt.ylabel('ln(max_error)', fontsize=16)
plt.plot(ln_h, ln_error, label='Numerical Derivative Errors', linewidth=2.0)
plt.scatter(ln_h, ln_error, color="red")
plt.grid(True)
plt.legend()
plt.show()
