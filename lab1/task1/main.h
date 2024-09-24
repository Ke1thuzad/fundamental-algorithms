#ifndef LAB1T1_MAIN_H
#define LAB1T1_MAIN_H

#include <stdio.h>
#include <stdlib.h>

#include "array.h"

typedef enum kOpts {
    OPT_H,
    OPT_P,
    OPT_S,
    OPT_E,
    OPT_A,
    OPT_F
} kOpts;

typedef enum errcode {
    OUT_OF_BOUNDS = 2,
    INCORRECT_OPTION
} errcode;

void natural_numbers(unsigned int);
void is_prime(unsigned int);
void to_base16(unsigned int);
long long power(unsigned int, unsigned int);
void exponent_table(unsigned int);
void natural_sum(unsigned int);
void factorial(unsigned int);

#endif
