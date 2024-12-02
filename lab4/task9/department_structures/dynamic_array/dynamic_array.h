#ifndef FUNDAMENTAL_ALGORITHMS_DYNAMIC_ARRAY_H
#define FUNDAMENTAL_ALGORITHMS_DYNAMIC_ARRAY_H

#include "../department.h"

typedef struct DepartmentArray {
    Department **departments;

    size_t length;
    size_t capacity;
} DepartmentArray;

DepartmentArray *create_department_array() {
    DepartmentArray *array = (DepartmentArray*) malloc(sizeof(DepartmentArray));
    if (!array)
        return NULL;

    array->length = 0;
    array->capacity = 10;
    array->departments = (Department **) calloc(array->capacity, sizeof(Department *));

    return array;
}

int resize_department_array(DepartmentArray *array, size_t size_delta);

int extend_department_array(DepartmentArray *array) {
    return resize_department_array(array, array->capacity);
}

int dichotomic_search_department_array(DepartmentArray *array, Department key, int *position) {
    int left = 0;
    int right = array->length;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = compare_str(array->departments[mid]->id, key.id);

        if (cmp == 0) {
            *position = mid;
            return 1;
        }

        if (cmp < 0)
            left = mid + 1;
        else
            right = mid;
    }

    *position = left;
    return 0;
}

int insert_department_array(DepartmentArray *array, Department *department) {
    if (array->length + 1 >= array->capacity) {
        int err = extend_department_array(array);
        if (err)
            return err;
    }

    int position;
    int found = dichotomic_search_department_array(array, *department, &position);

    if (found) {
        position++;
    }

    for (int i = array->length; i > position; i--) {
        array->departments[i] = array->departments[i - 1];
    }

    array->departments[position] = department; // TODO: copy?
    array->length++;

    return 0;
}

int find_least_overloaded_department_in_array(DepartmentArray *array, Department **result) {
    float eps = 0.00001f;

    float min_load = get_department_load(*array->departments[0]);
    *result = array->departments[0];

    for (int i = 0; i < array->length; ++i) {
        Department *cur_dep = array->departments[i];
        float cur_load = get_department_load(*cur_dep);

        if (cur_load - min_load < eps) {
            min_load = cur_load;
            *result = cur_dep;
        }
    }

    return 0;
}

void destroy_department_array(DepartmentArray *array);

#endif //FUNDAMENTAL_ALGORITHMS_DYNAMIC_ARRAY_H
