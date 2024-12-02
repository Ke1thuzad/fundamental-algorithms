#pragma once

#ifndef FUNDAMENTAL_ALGORITHMS_DEPARTMENT_H
#define FUNDAMENTAL_ALGORITHMS_DEPARTMENT_H

#include "department_structure.h"

#include <time.h>

String *randomize_operator_name();

Department *create_department(String id, HeapType heap_type, int total_operators, float overload_coefficient);

float get_department_load(Department department);

void destroy_department(Department *department);

#endif //FUNDAMENTAL_ALGORITHMS_DEPARTMENT_H
