
#include "dynamic_array.h"

DepartmentArray *create_department_array() {
    DepartmentArray *array = (DepartmentArray*) malloc(sizeof(DepartmentArray));
    if (!array)
        return NULL;

    array->length = 0;
    array->capacity = 10;
    array->departments = (Department **) calloc(array->capacity, sizeof(Department *));
    if (!array->departments) {
        free(array);
        return NULL;
    }

    return array;
}

int resize_department_array(DepartmentArray *array, size_t size_delta) {
    Department **temp = (Department **) realloc(array->departments, (array->capacity + size_delta) * sizeof(Department *));
    if (!temp) {
        destroy_department_array(array);
        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    array->departments = temp;
    array->capacity += size_delta;

    return 0;
}

int extend_department_array(DepartmentArray *array) {
    return resize_department_array(array, array->capacity);
}

int insert_department_array(DepartmentArray *array, Department *department) {
    if (!array || !department)
        return throw_err(INCORRECT_ARGUMENTS);

    if (array->length + 1 >= array->capacity) {
        int err = extend_department_array(array);
        if (err)
            return err;
    }

    int position = 0;
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

void destroy_department_array(DepartmentArray *array) {
    for (int i = 0; i < array->length; i++) {
        destroy_department(array->departments[i]);
        free(array->departments[i]);
    }

    free(array->departments);

    array->departments = NULL;
    array->length = 0;
    array->capacity = 0;

    free(array);
}

int get_from_department_array(DepartmentArray *array, String key, Department **result) {
    if (!array)
        return throw_err(INCORRECT_ARGUMENTS);

    int left = 0;
    int right = array->length - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = compare_str(array->departments[mid]->id, key);

        if (cmp == 0) {
            *result = array->departments[mid];

            return 1;  // Found
        }

        if (cmp < 0)
            left = mid + 1;
        else
            right = mid;
    }

    *result = NULL;
    return 0;  // Not found
}

int dichotomic_search_department_array(DepartmentArray *array, Department key, int *position) {
    if (!array || array->length <= 0)
        return 0;

    int left = 0;
    int right = array->length - 1;

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
