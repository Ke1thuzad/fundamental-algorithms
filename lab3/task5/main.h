#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include "../../utility/error_handler.h"
#include "../../utility/arrays/array.h"
#include "../../utility/overio.h"

#include <stdlib.h>

#define STDCAP 4

typedef enum SearchCriteria {
        ID,
        NAME,
        SURNAME,
        GROUP,
        MEAN
} SearchCriteria;

typedef union SearchParameter {
    unsigned int id;
    Array str;
    float mean;
} SearchParameter;

typedef struct Student {
    unsigned int id;
    Array name;
    Array surname;
    Array group;
    unsigned char *grades;
} Student;

typedef struct StudentArr {
    Student *val;
    unsigned int length;
    unsigned int capacity;
} StudentArr;


int check_paths(char* in, char *out);

int create_studarr(unsigned int length, StudentArr *arr);
int resize_stud(StudentArr *arr, int size_delta);
int extend_stud(StudentArr *arr);
int append_stud(StudentArr *arr, const Student value);
void destroy_stud(StudentArr *arr);
int read_students(FILE *in, StudentArr *students);
int student_search(const StudentArr students, int criteria, SearchParameter param, StudentArr *result);
int create_student(Student *student);
void reset_student(Student *student);
//int copy_student(Student *dst, Student *src);
void destroy_student(Student *student);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
