#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include "../../utility/error_handler.h"
#include "../../utility/arrays/intarray.h"

#include <stdarg.h>
#include <math.h>

int has_finite_representation(int base, int n, ...);
int gcd(int a, int b);
void reduce(int *numerator, int *denominator);
int fraction_approximation(double x, int* numerator, int* denominator);
int is_prime_factors_base(int x, int base);
void prime_factors(int x, IntArray* result);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
