
#include "dynamic_array.h"

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
