#ifndef LAB1T1_INTARRAY_H
#define LAB1T1_INTARRAY_H

typedef struct IntArray {
    int* val;
    unsigned int length;
    unsigned int capacity;
} IntArray;

int create_arr(unsigned int length, IntArray* arr);
int append(IntArray* arr, int value);
int resize(IntArray* arr, int size_delta);
int extend(IntArray* arr);
void destroy(IntArray* arr);
//int copy(IntArray* dst, IntArray* src);
//int reverse(IntArray* arr);
void print_arr(IntArray arr);

#endif //LAB1T1_INTARRAY_H
