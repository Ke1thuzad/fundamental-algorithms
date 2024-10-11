#include "main.h"

int main() {
    double res;
    int err;
    printf("Dichotomy method for ln(x) = 1:\n");
    err = dichotomy_method(0.01, equation_e, 0.0, 10.0, &res);
    if (err)
        return err;
    printf("%f\n", res);
    err = dichotomy_method(0.000000000001, equation_e, 2.0, 4.0, &res);
    if (err)
        return err;
    printf("%f\n", res);
    err = dichotomy_method(0.00001, equation_e, 0.5, 10.0, &res);
    if (err)
        return err;
    printf("%f\n", res);
    err = dichotomy_method(0.001, equation_e, -1.0, 3.0, &res);
    if (err)
        return err;

    printf("%f\n\n", res);
    printf("Dichotomy method for e^x = 2:\n");
    err = dichotomy_method(0.01, equation_ln2, 0.0, 10.0, &res);
    if (err)
        return err;
    printf("%f\n", res);
//    err = dichotomy_method(0.000000000001, equation_ln2, 2.0, 4.0, &res);
    if (err)
        return err;
    printf("%f\n", res);
    err = dichotomy_method(0.00001, equation_ln2, 0.5, 10.0, &res);
    if (err)
        return err;
    printf("%f\n", res);
    err = dichotomy_method(0.001, equation_ln2, -1.0, 3.0, &res);
    if (err)
        return err;
    printf("%f\n\n", res);

    printf("Dichotomy method for e^x * sin(x) = 0:\n");
    err = dichotomy_method(0.01, eq1, 2.0, 4.0, &res);
    if (err)
        return err;
    printf("%f\n", res);
    err = dichotomy_method(0.000000000001, eq1, -2.0, 1.0, &res);
    if (err)
        return err;
    printf("%f\n", res);
    err = dichotomy_method(0.00001, eq1, 0.5, 10.0, &res);
    if (err)
        return err;
    printf("%f\n", res);
    err = dichotomy_method(0.00001, eq1, -3.5, -0.5, &res);
    if (err)
        return err;
    printf("%f\n\n", res);

    return 0;
}
