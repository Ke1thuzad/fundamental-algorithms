#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../utility/error_handler.h"

typedef enum kOpts {
    OPT_D,
    OPT_I,
    OPT_S,
    OPT_A
} kOpts;

typedef int (*handler)(FILE*, char*);

int is_str_equal(char* str1, char* str2);
char* string_copy(char*, const char*);
int process_files(char*, char*, handler);
int is_num(int);
int handler_option_d(FILE*, char*);
int handler_option_i(FILE*, char*);
int handler_option_s(FILE*, char*);
int handler_option_a(FILE*, char*);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
