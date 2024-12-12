#ifndef FUNDAMENTAL_ALGORITHMS_DYNAMIC_ARRAY_H
#define FUNDAMENTAL_ALGORITHMS_DYNAMIC_ARRAY_H

#include "../department.h"

typedef struct DepartmentArray {
    Department **departments;

    size_t length;
    size_t capacity;
} DepartmentArray;

DepartmentArray *create_department_array();

int resize_department_array(DepartmentArray *array, size_t size_delta);

int extend_department_array(DepartmentArray *array);

int insert_department_array(DepartmentArray *array, Department *department);

int get_from_department_array(DepartmentArray *array, String key, Department **result);

int dichotomic_search_department_array(DepartmentArray *array, Department key, int *position);

//int find_least_overloaded_department_in_array(DepartmentArray *array, Department **result) {
//    float eps = 0.00001f;
//
//    float min_load = get_department_load(*array->departments[0]);
//    *result = array->departments[0];
//
//    for (int i = 0; i < array->length; ++i) {
//        Department *cur_dep = array->departments[i];
//        float cur_load = get_department_load(*cur_dep);
//
//        if (cur_load - min_load < eps) {
//            min_load = cur_load;
//            *result = cur_dep;
//        }
//    }
//
//    return 0;
//}

void destroy_department_array(DepartmentArray *array);

#endif //FUNDAMENTAL_ALGORITHMS_DYNAMIC_ARRAY_H
