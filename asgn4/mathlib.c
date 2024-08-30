#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#define M_PI 3.14159265358979323846
/*
 * Compute the absolute value of x.
 */
double Abs(double x) {
    return (x >= 0) ? x : -x;
}

/*
 * Compute the square root of x >= 0.
 */
double Sqrt(double x) {
    // Check domain.
    if (x < 0) {
        return nan("nan");
    }
    double old = 0.0;
    double new = 1.0;
    while (Abs(old - new) > EPSILON) {
        // Specifically, this is the Babylonian method--a simplification of
        // Newton's method possible only for Sqrt(x).
        old = new;
        new = 0.5 * (old + (x / old));
    }
    return new;
}

/*
 * Compute the sine of x.
 */
double Sin(double x) {
    double one = -1;
    int n = 1;
    double term = 0;
    double result = x;
    double pow = x * x * x;
    double factorial = 6;
    int fact = 3;
    do {
        if (n % 2 == 0) {
            one = 1;
        } else {
            one = -1;
        }
        term = (one / factorial) * (pow);
        result += term;
        factorial *= fact + 1;
        factorial *= fact + 2;
        n++;
        pow *= x;
        pow *= x;
        fact += 2;
    } while (Abs(term) >= EPSILON);
    return result;
}
/*
 * Compute the cosine of x.
 */
double Cos(double x) {
    double one = 0;
    int n = 1;
    double term = 0;
    double result = 1;
    double pow = x * x;
    double factorial = 2;
    int fact = 2;
    do {
        if (n % 2 == 0) {
            one = 1;
        } else {
            one = -1;
        }
        term = (one / factorial) * (pow);
        result += term;

        factorial *= fact + 1;
        factorial *= fact + 2;
        n++;
        pow *= x;
        pow *= x;
        fact += 2;
    } while (Abs(term) >= EPSILON);
    return result;
}

/*
 * Compute the tangent of x.
 */
double Tan(double x) {
    return Sin(x) / Cos(x);
}
