#include "main.h"

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


double integrate(double eps, double (*f)(double), double upper_bound, double lower_bound) {
    if (lower_bound > upper_bound) {
        throw_err(INCORRECT_ARGUMENTS);
    }

    double area = 0;
    double iter = (upper_bound - lower_bound) * eps;
    double prev = lower_bound;
    for (double x = lower_bound + iter; fabs(x - upper_bound) > eps; x += iter) {
        double mid = (x + prev) / 2.0;
        area += f(mid) * (x - prev);
        prev = x;
    }

    return area;
}

double func_a(double x) {
    return log(1 + x) / x;
}

double func_b(double x) {
    return exp(- x * x / 2);
}

double func_c(double x) {
    return log(1 / (1 - x));
}

double func_d(double x) {
    return pow(x, x);
}


