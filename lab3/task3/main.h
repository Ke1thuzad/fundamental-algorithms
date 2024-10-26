#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include "../../utility/error_handler.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct {
    unsigned int id;
    char name[1024];
    char surname[1024];
    float salary;
} Employee;

typedef struct {
    Employee *val;
    unsigned int length;
    unsigned int capacity;
} EmployeeArr;

typedef enum {
    ASCENDING,
    DESCENDING
} option;

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
