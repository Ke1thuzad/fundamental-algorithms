#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <stdio.h>
#include <limits.h>

#include "../../utility/error_handler.h"
#include "../../utility/arrays/array.h"

int is_str_equal(char* str1, char* str2);
int seek_char(FILE **f, int* result);
int read_value(FILE **f, Array* result, char first);
int chrtoint(char, int*);
int parse_int(char*, int*);
int parse_str(Array* result);
int is_alnum(int x);
int is_num(int x);
int is_letter(int x);
int to_lower(int x);
int base_char_to_dec(char x);
int to_decimal(Array x, unsigned char base, long long *result);
int to_base(unsigned long long x, unsigned char base, Array * result);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
