#include "main.h"
#include <math.h>

int chrtoint(char x) {
    int a = x - '0';
    if (a < 0 || a > 9) throw_err(NOT_A_NUMBER);
    return a;
}

double parse_double(char* str) {
    double real_part = 0;
    int i = 0, int_part = 0, point = 0, sign = 1, multiplier = 1;

    if (str[0] == '-') i++, sign = -1;

    while (str[i] != '\0') {
        if (str[i] == '.') {
            if (point) throw_err(INCORRECT_ARGUMENTS);
            point = i;
            i++;
            continue;
        }
        int number = chrtoint(str[i]);
        if (point) {
            real_part += (double)number / (multiplier *= 10);
        } else {
            int_part *= 10;
            int_part += number;
        }
        i++;
    }
    return sign * (int_part + real_part);
}

double eval_series(double eps, double x, double (*f)(double prev, double x, int n), int n) {
    double sum = 0, prev_sum, cur_val = 1, delta = 10;
    while (delta > eps) {
        prev_sum = sum;
        cur_val = f(cur_val, x, n++);
        sum += cur_val;
        delta = fabs(prev_sum - sum);
    }

    return sum;
}

double func_a(double prev, double x, int n) {
    if (n < 1) n = 1;
    return prev * x / n;
}

double func_b(double prev, double x, int n) {
    if (n == 0) return 1;
    return prev * (-1) * x * x / (2 * n * (2 * n - 1));
}

double func_c(double prev, double x, int n) {
    if (n == 0) return 1;
    return prev * ((27 * n * n * n * x * x) / (3 * n * (3 * n - 1) * (3 * n - 2)));
}

double func_d(double prev, double x, int n) {
    return prev * (-1) * x * x * (2.0 * n - 1) / (2.0 * n);
}
