#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <stdio.h>
#include <limits.h>

#include "../error_handler.h"
#include "../arrays/array.h"

int is_str_equal(char* str1, char* str2);
int parse_str(Array* result);
int is_num(int x);
int is_letter(int x);
int to_lower(int x);
int base_char_to_dec(char x);
int to_decimal(Array x, unsigned char base, long long *result);
int to_base(unsigned long long x, unsigned char base, Array * result);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
