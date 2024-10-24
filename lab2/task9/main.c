#include "main.h"

int main() {
    int err;
    err = has_finite_representation(2, 4, 0.5, 0.125, 0.375, 0.2);
    if (err)
        return err;
    err = has_finite_representation(3, 3, 0.333333333333333333333333333, 0.666666666666667, 0.1);
    if (err)
        return err;

    err = has_finite_representation(10, 4, 0.1, 0.2, 0.3, 1.0/9);
    if (err)
        return err;

    err = has_finite_representation(12, 3, 0.083333333333333333, 0.16666666666666666, 0.25);
    if (err)
        return err;

    err = has_finite_representation(16, 3, 0.0625, -0.125, 0.1875);
    if (err)
        return err;

    err = has_finite_representation(25, 1, 0.0032);
    if (err)
        return err;

    return 0;
}

int has_finite_representation(int base, int n, ...) {
    if (base < 2 || base > 36)
        return throw_err(INCORRECT_ARGUMENTS);

    va_list args;
    va_start(args, n);

    double elem;

    for (int i = 0; i < n; ++i) {
        elem = va_arg(args, double);
        if (elem <= 0 || elem >= 1)
            return throw_err(INCORRECT_ARGUMENTS);

        int numerator = 1;
        int denominator = 1;

        fraction_approximation(elem, &numerator, &denominator);

        if (is_prime_factors_base(denominator, base)) {
            printf("Fraction %d/%d has a finite representation in base %d.\n", numerator, denominator, base);
        } else {
            printf("Fraction %d/%d does not have a finite representation in base %d.\n", numerator, denominator, base);
        }
    }

    va_end(args);

    return 0;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void reduce(int *numerator, int *denominator) {
    int divisor = gcd(*numerator, *denominator);
    *numerator /= divisor;
    *denominator /= divisor;
}

// https://stackoverflow.com/a/57967080
int fraction_approximation(double x, int* numerator, int* denominator) {
    *numerator = 1;
    *denominator = (int)round(1.0 / (x - (int)x));

    double eps = 0.00001;
    double approximation = (double)*numerator / *denominator;
    double difference = approximation - x;

    while (fabs(difference) >= eps) {
        if (difference > 0) {
            int diffDenominator = (int)round(1.0 / difference);
            int newNumerator = *numerator * diffDenominator - *denominator;
            int newDenominator = *denominator * diffDenominator;
            *numerator = newNumerator;
            *denominator = newDenominator;
        } else {
            int diffDenominator = (int)round(1.0 / -difference);
            int newNumerator = *numerator * diffDenominator + *denominator;
            int newDenominator = *denominator * diffDenominator;
            *numerator = newNumerator;
            *denominator = newDenominator;
        }

        approximation = (double)*numerator / *denominator;
        difference = approximation - x;
    }

    reduce(numerator, denominator);
    return 0;
}

int is_prime_factors_base(int x, int base) {
    IntArray xFactors, baseFactors;
    int err = create_intarr(5, &xFactors);
    if (err)
        return err;

    err = create_intarr(5, &baseFactors);
    if (err) {
        destroy_int(&xFactors);
        return err;
    }

    prime_factors(x, &xFactors);
    prime_factors(base, &baseFactors);

    for (int i = 0; i < xFactors.length; ++i) {
        int k = 0;
        for (int j = 0; j < baseFactors.length; ++j) {
            if (xFactors.val[i] == baseFactors.val[j]) {
                k = 1;
                break;
            }
        }
        if (!k) {

            destroy_int(&xFactors);
            destroy_int(&baseFactors);
            return 0;
        }
    }

    destroy_int(&xFactors);
    destroy_int(&baseFactors);

    return 1;

}

void prime_factors(int x, IntArray* result) {
    int y = x;
    for (int i = 2; i < sqrt(x) + 1; ++i) {
        if (y % i == 0) {
            while (y % i == 0) {
                append_int(result, i);
                y /= i;
            }
        }
    }

    if (y > 1) {
        append_int(result, y);
    }
}
