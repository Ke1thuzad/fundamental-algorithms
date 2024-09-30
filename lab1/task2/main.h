#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H
#include <stdlib.h>
#include <math.h>
#include "../error_handler.h"

typedef long double (*limit_f)(int);
typedef long double (*series_f)(long double, int);
typedef long double (*equation_f)(long double);


int chrtoint(char);
long double parse_ldouble(char*);
long double compute_limit(long double, limit_f);
long double compute_series(long double, series_f, int, int);
long double dichotomy_method(long double, equation_f, long double, long double);
long double secant_method(long double, equation_f, long double, long double);
long double compute_limit_sqrt2(long double);
long double compute_series_sqrt2(long double);
long double compute_limit_pi(long double);


long double limit_e(int);
long double series_e(long double, int);
long double equation_e(long double);

long double limit_pi(int);
long double series_pi(long double, int);
long double equation_pi(long double);

long double limit_ln2(int);
long double series_ln2(long double, int);
long double equation_ln2(long double);

long double limit_sqrt2(long double, int);
long double series_sqrt2(int);
long double equation_sqrt2(long double);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
