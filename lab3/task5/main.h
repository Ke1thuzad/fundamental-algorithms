#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include "../../utility/error_handler.h"
#include "../../utility/arrays/array.h"
#include "../../utility/overio.h"

#include <stdlib.h>

#define STDCAP 4

typedef enum DialogFSM {
    COMMAND_WAIT,
    COMMAND_HANDLE,
    PARAMETER_WAIT
} DialogFSM;

typedef enum Command {
    HELP,
    PRINT,
    SEARCH,
    SORT
} Command;

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

char *string_copy(char *dst, const char *src);

int dialog_manager(FILE* in, FILE* out);
int wait_command(Command *result);
int handle_command(Command cmd, StudentArr *students, FILE *out);
int wait_param(Command cmd, int *param);
int wait_search_param(SearchCriteria criteria, SearchParameter *searchParam);

void cmd_description(Command cmd);
void help_cmd();
int print_cmd(FILE* out, StudentArr students, int param);
int search_cmd(StudentArr students, SearchCriteria criteria, SearchParameter searchParam, StudentArr *found_students);
int sort_cmd(StudentArr *students, int param);

int check_paths(char* in, char *out);

int create_studarr(unsigned int length, StudentArr *arr);
int resize_stud(StudentArr *arr, int size_delta);
int extend_stud(StudentArr *arr);
int append_stud(StudentArr *arr, Student value);
void destroy_stud(StudentArr *arr);
int create_student(Student *student);
void reset_student(Student *student);
//int copy_student(Student *dst, Student *src);
void destroy_student(Student *student);

int cmp_student_id(const void *a, const void *b);
int cmp_student_name(const void *a, const void *b);
int cmp_student_surname(const void *a, const void *b);
int cmp_student_group(const void *a, const void *b);

float student_mean(Student student);
float all_student_mean(StudentArr students);

int read_students(FILE *in, StudentArr *students);
int write_students(FILE *out, StudentArr students, int mean);
int student_search(StudentArr students, int criteria, SearchParameter param, StudentArr *result);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
