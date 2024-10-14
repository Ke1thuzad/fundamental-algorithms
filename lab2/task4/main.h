#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <stdio.h>
#include <stdarg.h>

#include "../../utility/arrays/array.h"
#include "../../utility/error_handler.h"

typedef struct Point {
    double x;
    double y;
} Point;

int is_convex(int n, ...);
int polynomial(double* result, double point, int n, ...);
int kaprekar_handler(int base, int n, ...);
int is_kaprekar(Array val, int base);


#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
