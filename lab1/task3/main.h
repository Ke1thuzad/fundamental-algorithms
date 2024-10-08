#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../utility/error_handler.h"

typedef enum kOpts {
    OPT_Q,
    OPT_M,
    OPT_T
} kOpts;

typedef int (*option)(char**);

int chrtoint(char, int*);
int parse_double(char*, double*);
int parse_int(char*, int*);
int option_q(char**);
int option_m(char**);
int option_t(char**);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
