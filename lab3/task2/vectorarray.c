#include "main.h"

int create_vector_arr(unsigned int length, VectorArray *arr) {

    arr->capacity = length;
    arr->length = 0;
    arr->val = (Vector *) malloc(length * sizeof(Vector));

    if (!arr->val)
        return throw_err(MEMORY_NOT_ALLOCATED);

    return 0;
}

int append_vector(VectorArray *arr, Vector value) {
    if (arr->length >= (arr->capacity - 1)) {
        int err = extend_vector(arr);
        if (err)
            return err;
    }

    Vector *cur = &arr->val[arr->length++];
    cur->coords = malloc(sizeof(double) * value.n);

    for (int i = 0; i < value.n; ++i) {
        cur->coords[i] = value.coords[i];
    }

    cur->n = value.n;
//     = value;
    return 0;
}

int resize_vector(VectorArray *arr, int size_delta) {
    Vector *new_addr = (Vector *) realloc(arr->val, arr->capacity + size_delta * sizeof(Vector));

    if (!new_addr) {
        free(arr->val);
        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    arr->val = new_addr;
    arr->capacity += size_delta;
    return 0;
}

int extend_vector(VectorArray *arr) {
    return resize_vector(arr, arr->capacity);
}

void destroy_vector(VectorArray *arr) {
    for (int i = 0; i < arr->length; ++i) {
        free(arr->val[i].coords);

        arr->val[i].coords = NULL;
        arr->val[i].n = 0;
    }

    if (arr->val)
        free(arr->val);

    arr->val = NULL;
    arr->length = 0;
    arr->capacity = 0;
}
