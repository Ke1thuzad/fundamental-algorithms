#include "main.h"

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int expansion_series(double eps, double a, double **result, int n, ...) {
    *result = (double *)malloc((n + 1) * sizeof(double));
    if (*result == NULL) {
        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    va_list args;
    va_start(args, n);

    double *coefficients = (double *)malloc((n + 1) * sizeof(double));
    if (coefficients == NULL) {
        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    for (int i = 0; i <= n; i++)
        coefficients[i] = va_arg(args, double);

    va_end(args);

    for (int i = 0; i <= n; i++) {
        double derivative = 0.0;
        for (int j = i; j <= n; j++) {
            // 1 + 2x + 3x^2
            // g[0] = (1 * a ^ 0 * 1 / 1 + 2 * a ^ 1 * 1 / 1 + 3 * a ^ 2 * 2 / 2) / 0! = 17
            double b = coefficients[j] * pow(a, j - i) * (double)factorial(j) / (double)factorial(j - i);
            if (fabs(b) < eps)
                break;

            derivative += b;
        }
        (*result)[i] = derivative / (double)factorial(i);
    }

    free(coefficients);
    return 0;
}

int main() {
    double *result;

    expansion_series(0.00001, 2.0, &result, 2, 1.0, 2.0, 3.0);

    for (int i = 0; i <= 3; i++) {
        printf("g[%d] = %f\n", i, result[i]);
    }

    free(result);

    return 0;
}