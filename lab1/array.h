#ifndef LAB1T1_ARRAY_H
#define LAB1T1_ARRAY_H

typedef struct Array {
    char* val;
    unsigned int length;
    unsigned int capacity;
} Array;

int create_arr(unsigned int length, Array* arr);
int append(Array* arr, char value);
int resize(Array* arr, int size_delta);
int extend(Array* arr);
void destroy(Array* arr);
void print_arr(Array arr);
void reverse_print_arr(Array arr);
int value_to_arr(unsigned int value, Array* result);
int str_to_arr(char* str, Array* result);

#endif //LAB1T1_ARRAY_H
