#include "main.h"

int chrtoint(char x, int* num) {
    int a = x - '0';
    if (a < 0 || a > 9) return throw_err(OUT_OF_BOUNDS);
    *num = a;
    return 0;
}

int parse_double(char* str, double *res) {
    double real_part = 0;
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
        if(err) {
            return err;
        }
        if (point) {
            real_part += (double)number / (multiplier *= 10);
        } else {
            int_part *= 10;
            int_part += number;
        }
        i++;
    }
    *res = sign * (int_part + real_part);
    return 0;
}


double geometric_mean(int n, ...) {
    va_list values;
    double prod = 1.0, elem;

    va_start(values, n);
    for (int i = n; i--;) {
        elem = va_arg(values, double);
        prod *= elem;
    }
    va_end(values);

    return pow(prod, 1.0 / n);
}

double fast_exponentiation(double x, int n) {
    if (n == 0)
        return 1;

    if (n < 0)
        return fast_exponentiation(1 / x, -n);

    if (n % 2 == 0)
        return fast_exponentiation(x * x, n*0.5);
    else
        return x * fast_exponentiation(x * x, (n - 1) / 2);

}
