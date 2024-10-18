#include "main.h"

int main() {

    has_finite_representation(2, 3, 0.5, 0.125, 0.375);
    has_finite_representation(3, 3, 0.333333333333333333333333333, 0.666666666666667, 0.1);
    has_finite_representation(10, 3, 0.1, 0.2, 0.3);
    has_finite_representation(12, 3, 0.083333333333333333, 0.16666666666666666, 0.25);
    has_finite_representation(16, 3, 0.0625, 0.125, 0.1875);

    return 0;
}

int has_finite_representation(int base, int n, ...) {
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
    int commonDivisor = gcd(*numerator, *denominator);
    *numerator /= commonDivisor;
    *denominator /= commonDivisor;
}

// https://stackoverflow.com/a/57967080
int fraction_approximation(double x, int* numerator, int* denominator) {
    *numerator = 1;
    *denominator = (int)round(1.0 / (x - (int)x));

    double eps = 0.00001;
    double currentApproximation = (double)*numerator / *denominator;
    double difference = currentApproximation - x;

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

        currentApproximation = (double)*numerator / *denominator;
        difference = currentApproximation - x;
    }

    reduce(numerator, denominator);
    return 0;
}

int is_prime_factors_base(int x, int base) {
    for (int i = 2; i <= sqrt(x); ++i) {
        if (x % i == 0) {
            if (base % i != 0 || base % (x / i) != 0)
                return 0;

            while (x % i == 0)
                x /= i;
        }
    }
    return 1;

}
