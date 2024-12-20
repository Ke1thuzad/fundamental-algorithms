#ifndef FUNDAMENTAL_ALGORITHMS_MYSTRING_H
#define FUNDAMENTAL_ALGORITHMS_MYSTRING_H

#include "../../utility/error_handler.h"

typedef struct String {
    char *val;
    unsigned int length;
    unsigned int capacity;
} String;

int create_str(String *arr, char *str);

int append_str(String *arr, char value);

void reset_str(String *arr);

int resize_str(String *arr, int size_delta);

int extend_str(String *arr);

void destroy_str(String *arr);

int copystr(String *dst, String *src);

int copy_newstr(String *dst, const String *src);

int concat_str(String *A, String B);

int compare_str(String a, String b);

int equiv_str(String a, String b);

int compare_str_and_cstr(String a, const char* b);

int read_value_string(FILE **f, String *result, char first);

#endif //FUNDAMENTAL_ALGORITHMS_MYSTRING_H
