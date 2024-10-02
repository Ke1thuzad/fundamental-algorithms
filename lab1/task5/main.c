#include "main.h"

int main(int argc, char** argv) {

    if (argc != 3)
        return throw_err(INCORRECT_ARGUMENTS);

    double eps, x;
    int err = parse_double(argv[1], &eps) | parse_double(argv[2], &x);
    if (err)
        return err;

    if (eps > 1 || eps < 0) {
        return throw_err(INCORRECT_ARGUMENTS);
    }

    printf("Series a: %f\n", eval_series(eps, x, func_a, 0));
    printf("Series b: %f\n", eval_series(eps, x, func_b, 0));
    if (fabs(x) > 1) {
        printf("Series c and d diverges if |x| > 1.\n");
        return 0;
    } else if (fabs(x) == 1) {
        printf("Series c diverges if |x| >= 1.\n");
    } else {
        printf("Series c: %f\n", eval_series(eps, x, func_c, 0));
    }
    printf("Series d: %f\n", eval_series(eps, x, func_d, 1));
    return 0;
}
