#include "array.h"
#include "error_handler.h"

int create_arr(unsigned int length, Array* arr) {
    arr->capacity = length;
    arr->length = 0;
    arr->val = malloc(length);

    if (!arr->val) return throw_err(MEMORY_NOT_ALLOCATED);

    return 0;
}

int append(Array* arr, char value) {
    if (arr->length >= (arr->capacity - 1)) {
        int err = extend(arr);
        if (err)
            return err;
    }

    arr->val[arr->length++] = value;
    arr->val[arr->length] = '\0';
    return 0;
}

int resize(Array* arr, int size_delta) {
    char* new_addr = realloc(arr->val, arr->capacity + size_delta);

    if (!new_addr)
        return throw_err(MEMORY_NOT_ALLOCATED);

    arr->val = new_addr;
    arr->capacity += size_delta;
    return 0;
}

// Double array length.
int extend(Array* arr) {
    return resize(arr, arr->capacity);
}

void destroy(Array* arr) {
    free(arr->val);
    arr->val = NULL;
    arr->length = 0;
    arr->capacity = 0;
}

void print_arr(const Array arr) {
    for (int i = 0; i < arr.length; ++i) {
        printf("%u ", arr.val[i]);
    }
}

void reverse_print_arr(const Array arr) {
    for (int i = arr.length - 1; i >= 0; --i) {
        printf("%u", arr.val[i]);
    }
}

int value_to_arr(unsigned int value, Array* result) {
    int err = create_arr(10, result);
    if (err)
        return err;
    while (value > 0) {
        err = append(result, value % 10);
        if (err)
            return err;
        value /= 10;
    }
    return 0;
}

int str_to_arr(char* str, Array* result) {
    if (result)
        destroy(result);
    int err = create_arr(10, result), i = 0;
    if (err)
        return err;
    while (str[i]) {
        err = append(result, str[i++]);
        if (err)
            return err;
    }
    return 0;

}

//Array multiply(const Array A, unsigned int B) {
//    Array result = create_arr(A.capacity + 5);
//    int shift = 0;
//
//    for (int i = 0; i < A.length; i++) {
//        int product = A.val[i] * B + shift;
//        shift = product / 10;
//        append(&result, product % 10);
//    }
//
//    while (shift > 0) {
//        append(&result, shift % 10);
//        shift /= 10;
//    }
//
//
//    return result;
//}