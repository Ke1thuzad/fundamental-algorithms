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
int handler_l(int argc, char **argv, Array *result);
int handler_r(int argc, char **argv, Array *result);
int handler_u(int argc, char **argv, Array *result);
int handler_n(int argc, char **argv, Array *result);
int handler_c(int argc, char **argv, Array *result);

typedef int (*option)(int argc, char **argv, Array *result);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
