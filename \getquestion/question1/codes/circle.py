import numpy as np
import matplotlib.pyplot as plt

def read_coordinates(file_path):
    """Reads coordinates from the specified file and returns them as tuples."""
    with open(file_path, 'r') as file:
        lines = file.readlines()
        # Strip any whitespace and handle potential non-numeric entries
        try:
            center = tuple(map(float, lines[1].strip().split()))
            point_a = tuple(map(float, lines[0].strip().split()))
            point_b = tuple(map(float, lines[2].strip().split()))
            return center, point_a, point_b
        except ValueError as e:
            raise ValueError(f"Error processing coordinates from file: {e}")

# Path to the coordinates file
file_path = 'coordinates.txt'

# Step 1: Read coordinates from the file
try:
    center, point_a, point_b = read_coordinates(file_path)
except Exception as e:
    print(e)
    exit()

# Step 2: Calculate the radius
def distance(p1, p2):
    return np.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)

radius = distance(point_a, point_b) / 2

# Circle center and points
center_x, center_y = center
point_a_x, point_a_y = point_a
point_b_x, point_b_y = point_b

# Generate circle points
theta = np.linspace(0, 2 * np.pi, 100)
circle_x = center_x + radius * np.cos(theta)
circle_y = center_y + radius * np.sin(theta)

# Plot the circle
plt.figure(figsize=(8, 8))
plt.plot(circle_x, circle_y, label='Circle', color='blue')

# Plot the points
plt.plot(center_x, center_y, 'ro', label='O (Center)')
plt.plot(point_a_x, point_a_y, 'go', label='A (End of Diameter)')
plt.plot(point_b_x, point_b_y, 'yo', label='B (End of Diameter)')

# Annotate the points
plt.text(center_x, center_y, 'O', fontsize=12, ha='right')
plt.text(point_a_x, point_a_y, 'A', fontsize=12, ha='left')
plt.text(point_b_x, point_b_y, 'B', fontsize=12, ha='left')

# Set aspect ratio to be equal
plt.gca().set_aspect('equal', adjustable='box')

# Add labels and legend
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Circle with Diameter Ends and Center')

plt.grid(True)

# Show plot
plt.show()

