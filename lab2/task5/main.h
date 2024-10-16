#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <stdarg.h>

#include "../../utility/error_handler.h"
#include "../../utility/arrays/array.h"
#include "../../utility/arrays/intarray.h"

int overfprintf(FILE* stream, const char* format, ...);
int oversprintf(char* buf, const char* format, ...);
int is_str_equal(char* str1, char* str2);
int snread_value(const char* str, char* result, int n, char first);
int to_roman_numeral(int a, Array* result);
int to_zeckendorf(unsigned int a, IntArray* result);
int max_fib(unsigned int n);
int to_base(int x, unsigned char base, Array * result, int lower);
int to_decimal(Array x, unsigned char base, Array *result);
void fprint_bits(size_t const size, void const *const ptr, FILE *stream);
void sprint_bits(size_t const size, void const *const ptr, char *buf);
int len(const char* str);
void string_concat(char* str1, const char* str2);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
