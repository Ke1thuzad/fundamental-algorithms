#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <stdio.h>

#include "../../utility/arrays/array.h"
#include "../../utility/error_handler.h"

typedef enum {
    OPT_R,
    OPT_A
} kOpts;

typedef int (*handler)(Array* paths);

int handler_r(Array* paths);
int handler_a(Array* paths);
int open_descriptors(Array* paths, char** flags, FILE** descriptors, int size);
int seek_char(FILE** f, int* result);
int read_value(FILE** f, Array* result, char first);
int is_letter(int x);
int is_num(int x);
int is_alnum(int x);
int to_lower(int x);
//int to_decimal(Array x, unsigned char base, long long *result);
int to_base(unsigned int x, unsigned char base, char * result, size_t res_size);
int is_unique(const Array* arr, int size);
int is_str_equal(char* str1, char* str2);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
