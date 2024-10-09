#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <stdio.h>
#include <stdarg.h>
#include <math.h>

#include "../../utility/error_handler.h"

int chrtoint(char x, int* num);
int parse_double(char*, double*);
double geometric_mean(int n, ...);
double fast_exponentiation(double x, int n);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
