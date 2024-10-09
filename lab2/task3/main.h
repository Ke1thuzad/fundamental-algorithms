#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <stdio.h>
#include <stdarg.h>

#include "../../utility/error_handler.h"

int len(const char* str);
int substr(const char* str, int n, const char* key, int m);
int shift_table(const char* template, int n, int* result);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
