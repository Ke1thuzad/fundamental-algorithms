#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include "../../utility/error_handler.h"
#include "../../utility/arrays/array.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct {
    unsigned int id;
    Array name;
    Array surname;
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
