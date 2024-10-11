#include "main.h"

int dichotomy_method(double eps, equation_f f, double lborder, double rborder, double *res) {
    if (f(lborder) * f(rborder) >= 0)
        return throw_err(INCORRECT_ARGUMENTS);

    if (eps < 0 || eps > 1)
        return throw_err(INCORRECT_ARGUMENTS);

    if (lborder > rborder) {
        double temp = lborder;
        lborder = rborder;
        rborder = temp;
    }

    double delta = 1, midpoint;

    while (fabs(delta) > eps) {
        midpoint = (lborder + rborder) / 2;
        delta = f(midpoint);
        if (delta * f(lborder) < 0)
            rborder = midpoint;
        else
            lborder = midpoint;
    }

    *res = midpoint;
    return 0;
}

double equation_e(double x) {
    return log(x) - 1;
}

double equation_ln2(double x) {
    return exp(x) - 2;
}

double eq1(double x) {
    return exp(x) * sin(x);
}
