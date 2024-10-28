#include "main.h"

int expansion_series(double eps, double a, double **result, int n, ...) {
    *result = (double *)malloc((n + 1) * sizeof(double));
    if (*result == NULL)
        return throw_err(MEMORY_NOT_ALLOCATED);


    va_list args;
    va_start(args, n);

    double *coefficients = (double *)malloc((n + 1) * sizeof(double));
    if (coefficients == NULL)
        return throw_err(MEMORY_NOT_ALLOCATED);


    for (int i = 0; i <= n; i++)
        coefficients[i] = va_arg(args, double);

    va_end(args);

    double fact_i = 1;

    for (int i = 0; i <= n; i++) {
        if (i > 0)
            fact_i *= i;

        double derivative = 0.0;
        double fact_j = fact_i;
        double fact_jmi = 1;
        double apow = 1;
        for (int j = i; j <= n; j++) {
            // 1 + 2x + 3x^2
            // g[0] = ((1 * a ^ 0 * 1 / 1) + (2 * a ^ 1 * 1 / 1) + (3 * a ^ 2 * 2 / 2)) / 0! = 17
            if (j > i) {
                fact_j *= j;
                fact_jmi *= j - i;
                apow *= a;
            }

            double b = coefficients[j] * apow * fact_j / fact_jmi;
            if (fabs(b) < eps) {
                break;
            }

            derivative += b;
        }
        (*result)[i] = derivative / fact_i;
    }

    free(coefficients);
    return 0;
}

int main() {
    double *result;
    int degree = 5;
    double a = 0.1;
    expansion_series(0.00001, a, &result, degree, 123.0, 5895.234, 95.9513, 5.0, 41.2, 5.99);

    for (int i = 0; i <= degree; i++) {
        printf("%f(x - %f)^%d ", result[i], a, i);
        if (i != degree)
            printf("+ ");
    }

    free(result);

    return 0;
}