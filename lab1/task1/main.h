#ifndef LAB1T1_MAIN_H
#define LAB1T1_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <string.h>

#include "../error_handler.h"
#include "array.h"

typedef enum kOpts {
    OPT_S = -1,
    OPT_H,
    OPT_P,
    OPT_E,
    OPT_A,
    OPT_F
} kOpts;

int natural_numbers(unsigned int);
int is_prime(unsigned int);
int to_base16(unsigned int, int);
int to_base(unsigned int x, unsigned char base, char* result, size_t res_size);
long long power(unsigned int, unsigned int);
int exponent_table(unsigned int);
int natural_sum(unsigned int);
int factorial(unsigned int);

#endif
