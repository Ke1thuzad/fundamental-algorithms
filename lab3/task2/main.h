#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include "../../utility/error_handler.h"

#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <limits.h>

typedef struct Vector {
    int n;
    double *coords;
} Vector;

typedef struct VectorArray {
    Vector *val;
    unsigned int length;
    unsigned int capacity;
} VectorArray;

typedef double (*norm_func)(Vector vector, va_list factors);

int create_vector_arr(unsigned int length, VectorArray *arr);
int append_vector(VectorArray *arr, Vector value);
int resize_vector(VectorArray *arr, int size_delta);
int extend_vector(VectorArray *arr);
void destroy_vector(VectorArray *arr);


#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
