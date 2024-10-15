import numpy as np
import sympy as sp

def generate_grid(a, b, step):
    return np.arange(a, b, step)

x = sp.Symbol('x')

f_sym = sp.cosh(sp.exp(-x**2))

f_1st_derivative_sym = sp.diff(f_sym, x)
f_2nd_derivative_sym = sp.diff(f_1st_derivative_sym, x)

f = sp.lambdify(x, f_sym, modules=['numpy'])
f_1st_derivative = sp.lambdify(x, f_1st_derivative_sym, modules=['numpy'])
f_2nd_derivative = sp.lambdify(x, f_2nd_derivative_sym, modules=['numpy'])
