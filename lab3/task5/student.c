#include "main.h"

int create_studarr(unsigned int length, StudentArr *arr) {
    arr->capacity = length;
    arr->length = 0;
    arr->val = (Student *) malloc(length * sizeof(Student));
    if (!arr->val) return throw_err(MEMORY_NOT_ALLOCATED);
    return 0;
}

int resize_stud(StudentArr *arr, int size_delta) {
    Student *new_addr = (Student *) realloc(arr->val, (arr->capacity + size_delta) * sizeof(Student));
    if (!new_addr) {
        free(arr->val);
        return throw_err(MEMORY_NOT_ALLOCATED);
    }
    arr->val = new_addr;
    arr->capacity += size_delta;
    return 0;
}

int extend_stud(StudentArr *arr) {
    return resize_stud(arr, arr->capacity);
}

int append_stud(StudentArr *arr, const Student value) {
    if (arr->length >= arr->capacity) {
        int err = extend_stud(arr);
        if (err) return err;
    }

    Student *cur = &arr->val[arr->length++];
    create_student(cur);

    cur->id = value.id;

    cur->grades = malloc(sizeof(unsigned char) * 5);
    for (int i = 0; i < 5; ++i) {
        cur->grades[i] = value.grades[i];
    }
    copy(&cur->name, &value.name);
    copy(&cur->surname, &value.surname);
    copy(&cur->group, &value.group);

    return 0;
}

void destroy_stud(StudentArr *arr) {
    for (int i = 0; i < arr->length; ++i)
        destroy_student(&arr->val[i]);

    if (arr->val)
        free(arr->val);

    arr->val = NULL;
    arr->length = 0;
    arr->capacity = 0;
}

int create_student(Student *student) {
    int err = create_arr(5, &student->name);
    if (err)
        return err;

    err = create_arr(5, &student->surname);
    if (err) {
        destroy(&student->name);
        return err;
    }

    err = create_arr(5, &student->group);
    if (err) {
        destroy(&student->name);
        destroy(&student->surname);
        return err;
    }

    student->grades = NULL;
    student->id = 0;

    return 0;
}

void reset_student(Student *student) {
    reset(&student->name);
    reset(&student->surname);
    reset(&student->group);
    student->grades = NULL;
}

//int copy_student(Student *dst, Student *src) {
//    dst->id = src->id;
//    int err = copy(&dst->name, &src->name);
//    if (err)
//        return err;
//
//    err = copy(&dst->surname, &src->surname);
//    if (err) {
//        destroy(&dst->name);
//        return err;
//    }
//
//    err = copy(&dst->group, &src->group);
//    if (err) {
//        destroy(&dst->name);
//        destroy(&dst->surname);
//        return err;
//    }
//
//    string_copy((char *) &dst->grades, (const char *) &src->grades);
//
//    return 0;
//}

void destroy_student(Student *student) {
    destroy(&student->name);
    destroy(&student->surname);
    destroy(&student->group);

    if (student->grades != NULL)
        free(student->grades);

    student->grades = NULL;
}
