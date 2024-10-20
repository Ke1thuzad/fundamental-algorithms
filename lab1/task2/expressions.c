#include "main.h"

long double limit_e(int n) {
    return pow(1 + 1.0/n, (double)n);
}

long double series_e(long double prev, int n) {
    if (n == 0) return prev;
    return prev * 1/n;
}

long double equation_e(long double x) {
    return logl(x) - 1;
}

long double series_pi(long double prev, int n) {
    if (n == 1) return 1;
    return prev * (-1 + 2.0 / (2.0 * n - 1));
}

long double equation_pi(long double x) {
    return cosl(x) + 1;
}


long double limit_ln2(int n) {
    return n * (pow(2, 1.0/n) - 1);
}

long double series_ln2(long double prev, int n) {
    if (n == 1) return 1;
    return prev * (1.0 / n - 1);
}

long double equation_ln2(long double x) {
    return expl(x) - 2;
}


long double limit_sqrt2(long double prev, int n) {
    return prev - (prev * prev) / 2.0 + 1;
}

long double series_sqrt2(int n) {
    if (n < 2) throw_err(OUT_OF_BOUNDS);
    return exp2l(exp2l(-n));
}

long double equation_sqrt2(long double x) {
    return x * x - 2;
}
