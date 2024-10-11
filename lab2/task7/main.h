#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <stdio.h>
#include <math.h>

#include "../../utility/error_handler.h"

typedef double (*equation_f)(double);

int dichotomy_method(double eps, equation_f f, double lborder, double rborder, double *res);
double equation_e(double x);
double equation_ln2(double x);
double eq1(double x);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
