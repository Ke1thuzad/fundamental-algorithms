#include "main.h"

char *string_copy(char *dst, const char *src) {
    char *dstaddr = dst;
    char *srcaddr = src;
    while ((*dstaddr++ = *srcaddr++));
    return dstaddr;
}

//int check_paths(char *in, char *out) {
//    char inbuf[1000], outbuf[1000];
//
//    realpath(in, inbuf);
//    realpath(out, outbuf);
//
//    if (is_str_equal(inbuf, outbuf)) {
//        return 1;
//    }
//
//    return 0;
//}

int read_students(FILE *in, StudentArr *students) {
    Student cur = {};
    int read = 1;
    int ch;

    int err = create_student(&cur);
    if (err)
        return err;

    while (1) {
        unsigned char first_grade = 0;
        int scan_read = overfscanf(in, "%u %S %S %S %hhu", &cur.id, &cur.name, &cur.surname, &cur.group, &first_grade);
        if (scan_read == -1)
            break;

        if (scan_read != 5 || cur.name.length == 0 || cur.surname.length == 0 || cur.group.length == 0) {
            destroy_student(&cur);
            return throw_err(INCORRECT_INPUT_DATA);
        }

        unsigned char *cur_grades = malloc(sizeof(unsigned char) * STDCAP);
        if (!cur_grades) {
            destroy_student(&cur);
            return throw_err(MEMORY_NOT_ALLOCATED);
        }

        cur_grades[0] = first_grade;
        int length = 1, capacity = STDCAP;

        ch = fgetc(in);

        while (ch != '\n' && ch != EOF) {
            if (is_alnum(ch)) {
                if (length + 1 >= capacity) {
                    unsigned char *temp = realloc(cur_grades, capacity * 2);
                    if (!temp) {
                        destroy_student(&cur);
                        return throw_err(MEMORY_NOT_ALLOCATED);
                    }

                    cur_grades = temp;
                }

                cur_grades[length++] = ch - '0';
            }
            ch = fgetc(in);
        }

        cur.grades = cur_grades;

        if (length != 5) {
            destroy_student(&cur);
            return throw_err(INCORRECT_INPUT_DATA);
        }

        append_stud(students, cur);
        read++;
        free(cur.grades);

        reset_student(&cur);
    }

    destroy_student(&cur);

    return 0;
}

int write_students(FILE *out, StudentArr students, int mean) {
    for (int i = 0; i < students.length; ++i) {
        Student cur = students.val[i];
        fprintf(out, "%.3d | %s %s | %s | ", cur.id, cur.name.val, cur.surname.val, cur.group.val);
        printf("%.3d | %s %s | %s | ", cur.id, cur.name.val, cur.surname.val, cur.group.val);
        if (mean) {
            fprintf(out, "%f", student_mean(cur));
            printf("%f", student_mean(cur));
        }
        else {
            for (int j = 0; j < 5; ++j) {
                fprintf(out, "%hhu ", cur.grades[j]);
                printf("%hhu ", cur.grades[j]);
            }
        }

        fprintf(out, "\n");
        printf("\n");
    }
    fprintf(out, "\n");
    printf("\n");

    return 0;
}

int cmp_student_id(const void *a, const void *b) {
    Student *student1 = (Student *) a;
    Student *student2 = (Student *) b;
    return student1->id > student2->id;
}

int cmp_student_name(const void *a, const void *b) {
    Student *student1 = (Student *) a;
    Student *student2 = (Student *) b;
    return arr_compare(student1->name, student2->name);
}

int cmp_student_surname(const void *a, const void *b) {
    Student *student1 = (Student *) a;
    Student *student2 = (Student *) b;
    return arr_compare(student1->surname, student2->surname);
}

int cmp_student_group(const void *a, const void *b) {
    Student *student1 = (Student *) a;
    Student *student2 = (Student *) b;
    return arr_compare(student1->group, student2->group);
}

float student_mean(Student student) {
    float mean = 0;

    for (int i = 0; i < 5; ++i) {
        mean += (float) student.grades[i] / 5.0f;
    }

    return mean;
}

float all_student_mean(StudentArr students) {
    float mean = 0;

    for (int i = 0; i < students.length; ++i) {
        mean += student_mean(students.val[i]);
    }

    return mean / (float) students.length;
}

// 0 - By ID, 1 - Name, 2 - Surname, 3 - Group, 4 - Mean of grades
int student_search(const StudentArr students, int criteria, SearchParameter param, StudentArr *result) {
    double eps = 0.0000001;
    int read = 0;

    for (int i = 0; i < students.length; ++i) {
        Student cur = students.val[i];
        switch (criteria) {
            case 0:
                if (cur.id == param.id) {
                    read++;
                    append_stud(result, cur);
                }

                break;
            case 1:
                if (is_arr_equal(cur.name, param.str)) {
                    read++;
                    append_stud(result, cur);
                }

                break;
            case 2:
                if (is_arr_equal(cur.surname, param.str)) {
                    read++;
                    append_stud(result, cur);
                }

                break;
            case 3:
                if (is_arr_equal(cur.group, param.str)) {
                    read++;
                    append_stud(result, cur);
                }

                break;
            case 4:
                if (student_mean(cur) - param.mean > eps) {
                    read++;
                    append_stud(result, cur);
                }

                break;
            default:
                return -1;
        }
    }

    return read;
}

