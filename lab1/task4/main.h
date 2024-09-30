#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../error_handler.h"

typedef enum kOpts {
    OPT_D,
    OPT_I,
    OPT_S,
    OPT_A
} kOpts;

typedef void (*handler)(FILE*, char*);

char* string_copy(char*, const char*);
void process_files(char*, char*, handler);
int is_num(int);
void handler_option_d(FILE*, char*);
void handler_option_i(FILE*, char*);
void handler_option_s(FILE*, char*);
void handler_option_a(FILE*, char*);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
