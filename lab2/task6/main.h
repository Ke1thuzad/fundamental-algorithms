#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include "../../utility/error_handler.h"
#include "../../utility/arrays/array.h"

#include <stdarg.h>
#include <stdio.h>

int len(const char* str);
void string_concat(char* str1, const char* str2);
int is_str_equal(char* str1, char* str2);
int snread_value(const char* str, char* result, int n, char first);
int roman_value(char c);
int unroman(char* str, int* result);
int zecken(unsigned int* result, ...);
int unzeckendorf(unsigned int *result, va_list args);


#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
