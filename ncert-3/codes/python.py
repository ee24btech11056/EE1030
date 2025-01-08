import ctypes
import numpy as np
import matplotlib.pyplot as plt

# Load the shared object file
lib = ctypes.CDLL('./libarea.so')

# Define the function prototypes
y1 = lib.y1
y2 = lib.y2
y1.restype = ctypes.c_double
y2.restype = ctypes.c_double
y1.argtypes = [ctypes.c_double]
y2.argtypes = [ctypes.c_double]

area = lib.area
area.restype = ctypes.c_double
area.argtypes = [ctypes.c_double, ctypes.c_double, ctypes.c_double]

# Call the area function
lower_limit, upper_limit, stepsize = 0, 1, 0.01
result = area(lower_limit, upper_limit, stepsize)
print(f"Approximated area using .so file: {result}")

# Fixing the plotting issue by converting arguments properly
x_values = np.linspace(lower_limit, upper_limit, 100)

# Convert values to c_double for compatibility with the .so functions
y1_values = [y1(ctypes.c_double(x)) for x in x_values]
y2_values = [y2(ctypes.c_double(x)) for x in x_values]

# Plotting
plt.plot(x_values, y1_values, label='y=x')
plt.plot(x_values, y2_values, label='y=x^2')
plt.fill_between(x_values, y1_values, y2_values, alpha=0.3)
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.grid(True)
plt.savefig('fig.pdf')
plt.show()

