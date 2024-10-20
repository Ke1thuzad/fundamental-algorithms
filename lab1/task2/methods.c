#include "main.h"

int chrtoint(char x, int *num) {
    int a = x - '0';
    if (a < 0 || a > 9) return throw_err(OUT_OF_BOUNDS);
    *num = a;
    return 0;
}

int parse_ldouble(char *str, long double *res) {
    long double real_part = 0;
    int i = 0, int_part = 0, point = 0, sign = 1, multiplier = 1;

    if (str[0] == '-') i++, sign = -1;

    while (str[i] != '\0') {
        if (str[i] == '.') {
            if (point) return throw_err(INCORRECT_ARGUMENTS);
            point = i;
            i++;
            continue;
        }
        int number, err = chrtoint(str[i], &number);
        if (err) {
            return err;
        }
        if (point) {
            real_part += (long double) number / (multiplier *= 10);
        } else {
            int_part *= 10;
            int_part += number;
        }
        i++;
    }
    *res = sign * (int_part + real_part);
    return 0;
}

long double compute_limit(long double eps, limit_f f) {
    int n = 1;
    long double delta = +INFINITY, res = f(n), prev;

    while (delta > eps) {
        prev = res;
        n++;
        res = f(n);
        delta = fabsl(prev - res);
    }

    return res;
}

long double compute_series(long double eps, series_f f, int multiplier, int n) {
    long double sum = 0, prev_sum, cur_val = f(1, n), delta = +INFINITY;
    while (delta > eps) {
        prev_sum = sum;
        cur_val = f(cur_val, n++);
        sum += cur_val;
        delta = fabsl(prev_sum - sum);
    }

    return multiplier * sum;
}

int dichotomy_method(long double eps, equation_f f, long double lborder, long double rborder, long double *res) {
    if (f(lborder) * f(rborder) >= 0) {
//        printf_s("Wrong interval");
        return throw_err(INCORRECT_ARGUMENTS);
//        return 0;
    }

    long double delta = +INFINITY, midpoint;

    while (fabsl(delta) > eps) {
        midpoint = (lborder + rborder) / 2;
        delta = f(midpoint);
        if (delta * f(lborder) < 0)
            rborder = midpoint;
        else
            lborder = midpoint;
    }
    *res = midpoint;
    return 0;
}

long double secant_method(long double eps, equation_f f, long double x0, long double x1) {
    long double x_prev = x0, x = x1, x_next;
    long double delta = +INFINITY;

    while (delta > eps) {
        x_next = x - f(x) * (x - x_prev) / (f(x) - f(x_prev));
        delta = fabsl(x_next - x);
        x_prev = x;
        x = x_next;
    }

    return x;
}

long double compute_limit_sqrt2(long double eps) {
    int n = 1;
    long double delta = +INFINITY, res = -0.5, prev;
    while (delta > eps) {
        prev = res;
        res = limit_sqrt2(prev, n++);
        delta = fabsl(prev - res);
    }

    return res;
}


long double compute_series_sqrt2(long double eps) {
    int n = 1;
    long double prod = 1, prev_prod, cur_val, delta = +INFINITY;
    while (delta > eps) {
        prev_prod = prod;
        cur_val = series_sqrt2(++n);
        prod *= cur_val;
        delta = fabsl(prev_prod - prod);
    }

    return prod;
}

long double compute_limit_pi(long double eps) {
    int n = 2;
    long double prev_val, cur_val = 4, delta = +INFINITY;
    while (delta > eps) {
        prev_val = cur_val;
        cur_val *= (4.0 * n * (n - 1)) / powl(2 * n - 1, 2.0);
        delta = fabsl(cur_val - prev_val);
        n++;
    }

    return cur_val;
}