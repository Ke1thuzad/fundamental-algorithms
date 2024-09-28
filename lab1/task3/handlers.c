#include "main.h"

int chrtoint(char x) {
    int a = x - '0';
    if (a < 0 || a > 9) exit(NOT_A_NUMBER);
    return a;
}

double parse_double(char* str) {
    double real_part = 0;
    int i = 0, int_part = 0, point = 0, sign = 1;

    if (str[0] == '-') i++, sign = -1;

    while (str[i] != '\0') {
        if (str[i] == '.') {
            if (point) exit(INCORRECT_ARGUMENTS);
            point = i;
            i++;
            continue;
        }
        int number = chrtoint(str[i]);
        if (point) {
            real_part += number / pow(10.0, (double)(i - point));
        } else {
            int_part *= 10;
            int_part += number;
        }
        i++;
    }
    return sign * (int_part + real_part);
}

int parse_int(char* str) {
    int i = 0, result = 0, sign = 1;

    if (str[0] == '-') i++, sign = -1;

    while (str[i] != '\0') {
        result *= 10;
        result += chrtoint(str[i]);
        i++;
    }
    if (result == 0) exit(INCORRECT_ARGUMENTS);

    return sign * result;
}

void option_q(char** argv) {
    int i = 0;
    double eps = parse_double(argv[i++]), coefficients[3];

    for(; i < 4; ++i) {
        coefficients[i - 1] = parse_double(argv[i]);
    }
    for (i = 0; i < 3; ++i) {
        double a = coefficients[i];
        if (fabs(a) < eps) continue;
        for (int j = 0; j < 3; ++j) {
            if (j == i) continue;
            double b = coefficients[j];
            for (int k = 0; k < 3; ++k) {
                if (k == i || k == j) continue;
                double c = coefficients[k];
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
}

void option_m(char** argv) {
    int a = parse_int(argv[0]), b = parse_int(argv[1]);
    if (a % b == 0) {
        printf("Value %d is a multiple of %d", a, b);
    } else {
        printf("Value %d is not a multiple of %d", a, b);
    }
}

void option_t(char** argv) {
    int i = 0, mx_id = -1;
    double eps = parse_double(argv[i++]), coefficients[3], mx = -1, sum_sqr = 0;

    for(; i < 4; ++i) {
        coefficients[i - 1] = parse_double(argv[i]);
        if (coefficients[i - 1] > mx) {
            mx = coefficients[i - 1];
            mx_id = i - 1;
        }
    }

    for (i = 0; i < 3; ++i) {
        if (i == mx_id) continue;
        sum_sqr += pow(coefficients[i], 2.0);
    }

    if (fabs(sum_sqr - mx * mx) < eps) {
        printf("%f, %f and %f are the sides of the right tri.\n", coefficients[0], coefficients[1], coefficients[2]);
    } else {
        printf("Values cannot be the sides of a right tri.\n");
    }
}

