#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include "../../utility/overio.h"
#include "../../utility/arrays/array.h"

#include <stdio.h>

typedef struct Result {
    int level;
    Array *val;
} Result;

typedef struct ResultArr {
    Result *val;
    unsigned int length;
    unsigned int capacity;
} ResultArr;

int parse_expression(FILE *in, FILE *out);

int check_paths(char *in, char *out);

int create_result_arr(unsigned int length, ResultArr *arr);
int append_result(ResultArr *arr, Result *value);
int resize_results(ResultArr *arr, int size_delta);
int extend_result(ResultArr *arr);
void destroy_results(ResultArr *arr);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
