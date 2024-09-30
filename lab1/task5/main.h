#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <stdio.h>
#include <math.h>

#include "../error_handler.h"

int chrtoint(char);
double parse_double(char*);
double eval_series(double eps, double x, double (*f)(double prev, double x, int n), int n);
double func_a(double prev, double x, int n);
double func_b(double prev, double x, int n);
double func_c(double prev, double x, int n);
double func_d(double prev, double x, int n);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
