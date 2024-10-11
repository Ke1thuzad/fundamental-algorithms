#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <stdio.h>
#include <stdarg.h>

#include "../../utility/error_handler.h"

typedef struct Point {
    double x;
    double y;
} Point;


int polynomial(double* result, double point, int n, ...);


#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
