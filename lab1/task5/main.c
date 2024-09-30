#include "main.h"

int main(int argc, char** argv) {

    if (argc != 3)
        throw_err(INCORRECT_ARGUMENTS);

    double eps = parse_double(argv[1]);
    double x = parse_double(argv[2]);

    if (eps > 1 || eps < 0) {
        throw_err(INCORRECT_ARGUMENTS);
    }

    printf("Series a: %f\n", eval_series(eps, x, func_a, 0));
    printf("Series b: %f\n", eval_series(eps, x, func_b, 0));
    if (fabs(x) > 1) {
        printf("Series c and d diverge if |x| > 1.\n");
        return 0;
    } else if (fabs(x) == 1) {
        printf("Series c diverge if |x| >= 1.\n");
    } else {
        printf("Series c: %f\n", eval_series(eps, x, func_c, 0));
    }
    printf("Series d: %f\n", eval_series(eps, x, func_d, 1));
    return 0;
}
