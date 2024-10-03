#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <stdio.h>

#include "../error_handler.h"
#include "../array.h"

int handler(Array* paths);
int open_descriptors(Array* paths, char** flags, FILE** descriptors, int size);
int seek_char(FILE** f, int* result);
int read_value(FILE** f, Array* result);
int is_alnum(int x);
int is_num(int x);
int is_letter(int x);
int to_lower(int x);
int base_char_to_dec(char x);
int to_decimal(Array x, unsigned char base, Array *result);
int convert_base(Array* x, int from_base, int to_base, Array* result);

int is_unique(const Array* arr, int size);
int is_str_equal(char* str1, char* str2);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
