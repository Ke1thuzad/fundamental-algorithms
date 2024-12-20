#include "main.h"
#include <stdio.h>

int main(int argc, char** argv) {
    if (argc != 2)
        return throw_err(INCORRECT_ARGUMENTS);

    long double eps, eq_res;
    int err = parse_ldouble(argv[1], &eps);
    if (err)
        return err;

    if (eps <= 0)
        return throw_err(INCORRECT_ARGUMENTS);

    printf("e Calculation:\n");
    printf("Limit of e: %.16Lf | ", compute_limit(eps, &limit_e));
    printf("Series of e: %.16Lf | ", compute_series(eps, &series_e, 1, 0));
    err = dichotomy_method(eps, &equation_e, 0.5, 3.0, &eq_res);

    if (err)
        return err;
    printf("Equation of e: %.16Lf\n", eq_res);

    printf("pi Calculation:\n");
    printf("Limit of pi: %.16Lf | ", compute_limit_pi(eps));
    printf("Series of pi: %.16Lf | ", compute_series(eps, &series_pi, 4, 1));
    printf("Equation of pi: %.16Lf\n", secant_method(eps, &equation_pi, 2.5, 3.5));

    printf("sqrt2 Calculation:\n");
    printf("Limit of sqrt2: %.16Lf | ", compute_limit_sqrt2(eps));
    printf("Series of sqrt2: %.16Lf | ", compute_series_sqrt2(eps));
    err = dichotomy_method(eps, &equation_sqrt2, 1.0, 2.0, &eq_res);
    if (err)
        return err;
    printf("Equation of sqrt2: %.16Lf\n", eq_res);

    printf("ln2 Calculation:\n");
    printf("Limit of ln2: %.16Lf | ", compute_limit(eps, &limit_ln2));
    printf("Series of ln2: %.16Lf | ", compute_series(eps, &series_ln2, 1, 1));
    err = dichotomy_method(eps, &equation_ln2, 0.0, 1.0, &eq_res);
    if (err)
        return err;
    printf("Equation of ln2: %.16Lf\n", eq_res);

    return 0;
}
