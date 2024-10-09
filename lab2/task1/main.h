#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../utility/error_handler.h"
#include "../../utility/arrays/array.h"

typedef enum kOpts {
    OPT_L,
    OPT_R,
    OPT_U,
    OPT_N,
    OPT_C
} kOpts;

int to_upper(int x);
int is_alnum(int x);
int is_num(int x);
int is_letter(int x);
int handler_l(char **argv, Array *result);
int handler_r(char **argv, Array *result);
int handler_u(char **argv, Array *result);
int handler_n(char **argv, Array *result);
int handler_c(char **argv, Array *result);

typedef int (*option)(char **argv, Array *result);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
