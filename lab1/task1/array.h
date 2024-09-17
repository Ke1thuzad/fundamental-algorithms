#ifndef LAB1T1_ARRAY_H
#define LAB1T1_ARRAY_H

typedef struct Array {
    unsigned char* val;
    unsigned int length;
    unsigned int capacity;
} Array;

Array create_arr(unsigned int);
int append(Array*, unsigned char);
void resize(Array*, int);
void extend(Array*);
void print_arr(Array);
void reverse_print_arr(Array);
Array value_to_arr(unsigned int);
Array multiply(Array, unsigned int);

#endif //LAB1T1_ARRAY_H
