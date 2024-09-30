#include "main.h"

int main(int argc, char** argv) {

    if (argc != 2)
        throw_err(INCORRECT_ARGUMENTS);

    double eps = parse_double(argv[1]);

    if (eps > 1 || eps < 0) {
        throw_err(INCORRECT_ARGUMENTS);
    }

    printf("Integral a: %f\n", integrate(eps, func_a, 1, 0));
    printf("Integral b: %f\n", integrate(eps, func_b, 1, 0));
    printf("Integral c: %f\n", integrate(eps, func_c, 1, 0));
    printf("Integral d: %f\n", integrate(eps, func_d, 1, 0));

    return 0;
}
