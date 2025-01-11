import ctypes
import numpy as np
import matplotlib.pyplot as plt

# Load the shared library
solver = ctypes.CDLL('./trapezoidal_solver.so')

solver.solve_trapezoidal.argtypes = [ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_int, ctypes.POINTER(ctypes.c_double)]

# Parameters
x0 = 1.0
y0 = 1.0
h = 0.001

# Set the number of steps directly instead of limiting by x_max
steps = 5000  # Adjust the number of steps as needed for desired range

# Prepare array for results
results = (ctypes.c_double * steps)()
solver.solve_trapezoidal(x0, y0, h, steps, results)

# Convert results to NumPy array for plotting
y_trapezoidal = np.array(results)
x_values = np.linspace(x0, x0 + h * (steps - 1), steps)

# Analytical solution: y = x^2 + log|x|
y_analytical = x_values**2 + np.log(np.abs(x_values))

# Plot both graphs for the extended range
plt.figure(figsize=(10, 6))
plt.plot(x_values, y_trapezoidal, marker='o', label="Trapezoidal Approximation", linestyle='--')
plt.plot(x_values, y_analytical, label=r"$y = x^2 + \log|x|$", color='red')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.grid(True)
plt.savefig('fig.pdf')
plt.show()

