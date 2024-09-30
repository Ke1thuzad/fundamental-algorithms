#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../error_handler.h"

int chrtoint(char);
double parse_double(char*);
double integrate(double, double (*)(double), double, double);
double func_a(double);
double func_b(double);
double func_c(double);
double func_d(double);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
