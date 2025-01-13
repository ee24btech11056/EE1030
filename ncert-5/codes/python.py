import ctypes
import numpy as np
import matplotlib.pyplot as plt

# Load the shared library
gradient_ascent = ctypes.CDLL("./gradient_ascent.so")

# Define the function prototype for the C function
gradient_ascent.find_maximum.argtypes = [
    ctypes.c_double, ctypes.c_int, 
    ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double)
]
gradient_ascent.find_maximum.restype = None

# Wrapper function for calling the C function
def find_maximum(learning_rate, max_iterations):
    max_x_1 = ctypes.c_double()
    max_x_2 = ctypes.c_double()
    max_val_1 = ctypes.c_double()
    max_val_2 = ctypes.c_double()
    
    gradient_ascent.find_maximum(
        learning_rate, max_iterations,
        ctypes.byref(max_x_1), ctypes.byref(max_x_2),
        ctypes.byref(max_val_1), ctypes.byref(max_val_2)
    )
    return max_x_1.value, max_val_1.value, max_x_2.value, max_val_2.value

# Call the corrected C function
learning_rate = 0.01
max_iterations = 1000
max_x_1, max_value_1, max_x_2, max_value_2 = find_maximum(learning_rate, max_iterations)

print(f"Maximum value at x={max_x_1} is {max_value_1}")
print(f"Maximum value at x={max_x_2} is {max_value_2}")

# Define the function for plotting
def function(x):
    return (x**2 - x + 1)**(1/3)

# Generate data for plotting
x_values = np.linspace(0, 1, 500)
y_values = function(x_values)

# Plot the graph and both maximum points
plt.figure(figsize=(8, 6))
plt.plot(x_values, y_values, label="f(x) = (x² - x + 1)^(1/3)")
plt.scatter([max_x_1, max_x_2], [max_value_1, max_value_2], color="red", s=100, label="Max Points (x=0,1)")
plt.xlabel("x")
plt.ylabel("f(x)")
plt.legend()
plt.grid()
plt.savefig('fig.pdf')
plt.show()

