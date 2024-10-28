#ifndef FUNDAMENTAL_ALGORITHMS_MYSTRING_H
#define FUNDAMENTAL_ALGORITHMS_MYSTRING_H

#include "../../utility/error_handler.h"

typedef struct String {
    char *val;
    unsigned int length;
    unsigned int capacity;
} String;

int create_str(unsigned int length, String *arr);

int append_str(String *arr, char value);

void reset_str(String *arr);

int resize_str(String *arr, int size_delta);

int extend_str(String *arr);

void destroy_str(String *arr);

int copystr(String *dst, String *src);

int copy_newstr(String *dst, String *src);

int concat_str(String *A, String B);

#endif //FUNDAMENTAL_ALGORITHMS_MYSTRING_H
