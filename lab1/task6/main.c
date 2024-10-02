#include "main.h"

int main(int argc, char** argv) {

    if (argc != 2)
        return throw_err(INCORRECT_ARGUMENTS);

    double eps, res;
    int err = parse_double(argv[1], &eps);
    if (err)
        return err;

    if (eps > 1 || eps < 0) {
        return throw_err(INCORRECT_ARGUMENTS);
    }
    err = integrate(eps, func_a, 1, 0, &res);
    printf("Integral a: %f\n", res);
    err |= integrate(eps, func_b, 1, 0, &res);
    printf("Integral b: %f\n", res);
    err |= integrate(eps, func_c, 1, 0, &res);
    printf("Integral c: %f\n", res);
    err |= integrate(eps, func_d, 1, 0, &res);
    printf("Integral d: %f\n", res);

    return err;
}
