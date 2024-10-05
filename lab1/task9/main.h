#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../error_handler.h"
#include "../arrays/intarray.h"

int chrtoint(char, int*);
int parse_int(char*, int*);
int part_one(int a, int b);
int part_two();
int fill_array(IntArray* arr, int a, int b);
int binary_search_closest(IntArray arr, int key);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
