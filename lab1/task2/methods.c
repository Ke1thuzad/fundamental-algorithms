#include "main.h"

long double compute_limit(long double eps, limit_f f) {
    int n = 1;
    long double delta = 1, res = f(n), prev;
    while (delta > eps) {
        prev = res;
        n += 100;
        res = f(n);
        delta = fabsl(prev - res);
    }
    return res;
}

long double compute_series(long double eps, series_f f, int multiplier, int n) {
    long double sum = 0, prev_sum, cur_val = f(1, n), delta = 1;
     while (delta > eps) {
        prev_sum = sum;
        cur_val = f(cur_val, n++);
        sum += cur_val;
        delta = fabsl(prev_sum - sum);
    }

    return multiplier * sum;
}

long double dichotomy_method(long double eps, equation_f f, long double lborder, long double rborder) {
    if (f(lborder) * f(rborder) >= 0) {
//        printf_s("Wrong interval");
        exit(2);
        return 0;
    }

    long double delta = 1, midpoint;

    while (fabsl(delta) > eps) {
        midpoint = (lborder + rborder) / 2;
        delta = f(midpoint);
        if (delta * f(lborder) < 0)
            rborder = midpoint;
        else
            lborder = midpoint;
    }

    return midpoint;
}

long double compute_limit_sqrt2(long double eps) {
    int n = 1;
    long double delta = 1, res = -0.5, prev;
    while (delta > eps) {
        prev = res;
        res = limit_sqrt2(prev, n++);
        delta = fabsl(prev - res);
    }

    return res;
}


long double compute_series_sqrt2(long double eps) {
    int n = 2;
    long double prod = 0, prev_prod, cur_val = 1, delta = 1;
    while (delta > eps) {
        prev_prod = prod;
        cur_val = series_sqrt2(n++);
        prod *= cur_val;
        delta = fabsl(prev_prod - prod);
    }

    return prod;
}