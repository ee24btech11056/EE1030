#include <math.h>

// Definitions for y=x and y=x^2
double y1(double x) {
    return x;
}

double y2(double x) {
    return x * x;
}

// Trapezoidal area calculation
double area(double lower_limit, double upper_limit, double stepsize) {
    double total_area = 0;
    for (double i = lower_limit; i < upper_limit; i += stepsize) {
        double f1 = y1(i) - y2(i);
        double f2 = y1(i + stepsize) - y2(i + stepsize);
        total_area += 0.5 * stepsize * (f1 + f2);
    }
    return total_area;
}

