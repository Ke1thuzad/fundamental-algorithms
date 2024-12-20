#pragma once

#ifndef FUNDAMENTAL_ALGORITHMS_OVERIO_H
#define FUNDAMENTAL_ALGORITHMS_OVERIO_H

#include "arrays/array.h"
#include "error_handler.h"
#include "../lab3/task4/mystring.h"

#include <stdarg.h>
#include <stdio.h>

int overfscanf(FILE *stream, const char *format, ...);
int oversscanf(char *str, const char *format, ...);
int len(const char *str);
void string_concat(char *str1, const char *str2);
int is_str_equal(char *str1, char *str2);
int snread_value(const char *str, char *result, int n, char first);
//int read_value(FILE **f, Array* result, char first);
int skip_to_end_line();
int sread_value(char **s, Array *result, char first);
int sseek_char(char **s, char *result);
int roman_value(char c);
int unroman(char *str, int *result);
int unzeckendorf(unsigned int *result, FILE *stream);
int unzeckendorf_str(unsigned int *result, char **s);
int to_decimal(const Array x, unsigned char base, int *result);

#endif //FUNDAMENTAL_ALGORITHMS_OVERIO_H
