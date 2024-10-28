#include "mystring.h"

int create_str(unsigned int length, String *arr) {

    arr->capacity = length;
    arr->length = 0;
    arr->val = (char *) malloc(sizeof(char) * length);


    if (!arr->val) return throw_err(MEMORY_NOT_ALLOCATED);
    arr->val[0] = '\0';

    return 0;
}

int append_str(String *arr, char value) {
    if (arr->length >= (arr->capacity - 2)) {
        int err = extend_str(arr);
        if (err)
            return err;
    }

    arr->val[arr->length++] = value;
    arr->val[arr->length] = '\0';
    return 0;
}

void reset_str(String *arr) {
    arr->val[0] = '\0';
    arr->length = 0;
}

int resize_str(String *arr, int size_delta) {
    char *new_addr = (char *) realloc(arr->val, arr->capacity + size_delta * sizeof(char));

    if (!new_addr) {
        free(arr->val);
        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    arr->val = new_addr;
    arr->capacity += size_delta;
    return 0;
}

int extend_str(String *arr) {
    return resize_str(arr, arr->capacity);
}

void destroy_str(String *arr) {
    if (arr->val)
        free(arr->val);
    arr->val = NULL;
    arr->length = 0;
    arr->capacity = 0;
}

int copystr(String *dst, String *src) {
    destroy_str(dst);

    dst->val = (char *) calloc(src->capacity, sizeof(char));
    if (!dst->val)
        return throw_err(MEMORY_NOT_ALLOCATED);

    dst->length = src->length;
    dst->capacity = src->capacity;

    char *tempdst = dst->val, *tempsrc = src->val;
    while ((*dst->val++ = *src->val++));
    dst->val = tempdst;
    src->val = tempsrc;
    return 0;
}

int copy_newstr(String *dst, String *src) {
    int err = create_str(src->capacity, dst);
    if (err)
        return err;

    dst->length = src->length;

    char *tempdst = dst->val, *tempsrc = src->val;
    while ((*dst->val++ = *src->val++));
    dst->val = tempdst;
    src->val = tempsrc;
    return 0;
}

int concat_str(String *A, String B) {
    for (int i = 0; i < B.length; ++i) {
        int err = append_str(A, B.val[i]);
        if (err)
            return err;
    }

    return 0;
}

int compare_str(String a, String b) {
    if (a.length > b.length)
        return 1;
    else if (a.length < b.length)
        return -1;

    char* str1 = a.val;
    char* str2 = b.val;

    while (*str1 && *str2) {
        if (*str1 < *str2) return -1;
        if (*str1 > *str2) return 1;
        str1++;
        str2++;
    }
    if (*str1) return 1;
    if (*str2) return -1;
    return 0;
}

int equiv_str(String a, String b) {
    if (compare_str(a, b) == 0)
        return 1;
    return 0;
}