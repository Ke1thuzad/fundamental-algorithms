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

int parse_int(char* str, int* res) {
    int i = 0, result = 0, sign = 1;

    if (str[0] == '-') i++, sign = -1;

    while (str[i] != '\0') {
        int temp, err = chrtoint(str[i], &temp);
        if (err)
            return err;
        result *= 10;
        result += temp;
        i++;
    }
    if (result == 0) return throw_err(INCORRECT_ARGUMENTS);

    *res = sign * result;
    return 0;
}

int option_q(char** argv) {
    double eps, coefficients[3];
    int i = 0, err = parse_double(argv[i++], &eps);
    if (err)
        return err;

    for(; i < 4; ++i) {
        err = parse_double(argv[i], &coefficients[i - 1]);
        if (err)
            return err;
    }
    for (i = 0; i < 3; ++i) {
        double a = coefficients[i];
        for (int j = 0; j < 3; ++j) {
            if (j == i) continue;
            double b = coefficients[j];
            for (int k = 0; k < 3; ++k) {
                if (k == i || k == j) continue;
                double c = coefficients[k];
                if (fabs(a) < eps) {
                    printf("\nCoefficients: %f %f %f\n", a, b, c);
                    printf("Root: %f\n", -c / b);
                    continue;
                }
                double D = b * b - 4 * a * c;

                printf("\nCoefficients: %f %f %f\n", a, b, c);
                if (fabs(D) <= eps) {
                    double x = -b / (2 * a);
                    printf("Root: %f\n", x);
                } else if (D > eps) {
                    double x1 = (-b + sqrt(D)) / (2 * a), x2 = (-b - sqrt(D)) / (2 * a);
                    printf("Roots: %f %f\n", x1, x2);
                } else {
                    printf("No real roots\n");
                }

            }
        }
    }
    return 0;
}

int option_m(char** argv) {
    int a, b;
    int err = parse_int(argv[0], &a) | parse_int(argv[1], &b);
    if (err)
        return err;
    if (a % b == 0) {
        printf("Value %d is a multiple of %d", a, b);
    } else {
        printf("Value %d is not a multiple of %d", a, b);
    }
    return 0;
}

int option_t(char** argv) {
    int i = 0, mx_id = -1;
    double eps, coefficients[3], mx = -1, sum_sqr = 0;
    int err = parse_double(argv[i++], &eps);
    if (err)
        return err;

    for(; i < 4; ++i) {
        err = parse_double(argv[i], &coefficients[i - 1]);
        if (err)
            return err;
        if (coefficients[i - 1] > mx) {
            mx = coefficients[i - 1];
            mx_id = i - 1;
        }
    }

    for (i = 0; i < 3; ++i) {
        if (i == mx_id) continue;
        if (fabs(coefficients[i]) <= eps)
            return throw_err(INCORRECT_ARGUMENTS);
        sum_sqr += pow(coefficients[i], 2.0);
    }

    if (fabs(sum_sqr - mx * mx) < eps) {
        printf("%f, %f and %f are the sides of the right tri.\n", coefficients[0], coefficients[1], coefficients[2]);
    } else {
        printf("Values cannot be the sides of a right tri.\n");
    }
    return 0;
}

