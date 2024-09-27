#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum kOpts {
    OPT_Q,
    OPT_M,
    OPT_T
} kOpts;

typedef enum errcode {
    OUT_OF_BOUNDS = 2,
    NOT_A_NUMBER,
    INCORRECT_OPTION,
    INCORRECT_ARGUMENTS
} errcode;

typedef void (*option)(char**);

int chrtoint(char);
double parse_double(char*);
int parse_int(char*);
void option_q(char**);
void option_m(char**);
void option_t(char**);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
