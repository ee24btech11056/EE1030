import ctypes
import matplotlib.pyplot as plt

# Load the shared object
lib = ctypes.CDLL('./libprobability.so')

# Specify the argument and return types of the C function
lib.calculate_complement.argtypes = [ctypes.c_double]
lib.calculate_complement.restype = ctypes.c_double

# Call the function from the shared object
P_B = 0.48
P_B_complement = lib.calculate_complement(P_B)

# Print the result
print(f"P(B') = {P_B_complement}")

# PMF values
pmf_values = [P_B_complement, 1 - P_B_complement]
n_values = [1, 0]

# Plot using a stem plot
plt.stem(n_values, pmf_values, linefmt='b-', markerfmt='bo', basefmt="r-")

# Explicitly add markers at probability values
plt.scatter(n_values, pmf_values, color='red', zorder=3, label="PMF Points")

# Labels and title
plt.xlabel('n')
plt.ylabel("P(B' = n)")
plt.title("PMF of B' (Complement of B)")
plt.xticks(n_values, ['1', '0'])
plt.ylim(0, 1)  # Set y-axis limits

# Add legend
plt.legend()

# Show the plot
plt.show()

