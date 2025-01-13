#include <stdio.h>
#include <math.h>

// Function definition: f(x) = [x^2 - x + 1]^(1/3)
double function(double x) {
    return pow((x * x - x + 1), 1.0 / 3.0);
}

// Derivative of the function: f'(x)
double derivative(double x) {
    double g = (x * x - x + 1);
    double g_prime = 2 * x - 1;
    return (1.0 / 3.0) * pow(g, -2.0 / 3.0) * g_prime;
}

// Gradient ascent function to find the maximum point
double gradient_ascent(double start, double learning_rate, int max_iterations) {
    double x = start;
    for (int i = 0; i < max_iterations; i++) {
        double grad = derivative(x);
        if (grad > 0) {
            x += learning_rate * grad;  // Move right
        } else {
            x += learning_rate * grad;  // Move left
        }

        // Boundary checks to prevent overshooting
        if (x < 0) x = 0;
        if (x > 1) x = 1;

        // Stop if gradient is close to zero or reaches boundaries
        if (fabs(grad) < 1e-6) break;
    }
    return x;
}

// Wrapper to find the maximum values and return them
void find_maximum(double learning_rate, int max_iterations, double *max_x_1, double *max_x_2, double *max_val_1, double *max_val_2) {
    // Use gradient ascent from both boundaries to find maxima at x=0 and x=1
    *max_x_1 = gradient_ascent(0, learning_rate, max_iterations);  // Starting from x=0
    *max_x_2 = gradient_ascent(1, learning_rate, max_iterations);  // Starting from x=1

    // Calculate function values at both points
    *max_val_1 = function(*max_x_1);
    *max_val_2 = function(*max_x_2);
}

// Main function for testing purposes
int main() {
    double learning_rate = 0.01;
    int max_iterations = 1000;
    double max_x_1, max_x_2, max_val_1, max_val_2;

    // Call the function to find maximum points
    find_maximum(learning_rate, max_iterations, &max_x_1, &max_x_2, &max_val_1, &max_val_2);

    // Print results
    printf("Maximum value at x=%f is %f\n", max_x_1, max_val_1);
    printf("Maximum value at x=%f is %f\n", max_x_2, max_val_2);

    return 0;
}

