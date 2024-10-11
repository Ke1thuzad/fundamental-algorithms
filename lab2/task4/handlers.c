#include "main.h"

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

int is_convex(int n, ...) {
    va_list vals;
    Point point;

    va_start(vals, n);
    for (int i = n; --i;) {
        point = va_arg(vals, Point);
    }
    va_end(vals);

    return 0;
}

int polynomial(double *result, double point, int n, ...) {
    if (n < 0)
        return throw_err(INCORRECT_ARGUMENTS);

    va_list vals;

    double coefficients[n];
    *result = 0;

    va_start(vals, n);
    for (int i = 0; i < n; ++i) {
        coefficients[i] = va_arg(vals, double);
    }
    va_end(vals);

    for (int i = n - 2; i >= 0; --i) {
        *result += coefficients[i] * point;
    }

    *result += coefficients[n - 1];

    return 0;
}
