#include "main.h"

char *string_copy(char *dst, const char *src) {
    char *dstaddr = dst;
    while ((*dst++ = *src++));
    return dstaddr;
}

int check_paths(char *in, char *out) {
    char *real_in = realpath(in, NULL);
    char *real_out = realpath(out, NULL);
    if (!(real_in && real_out)) {
        free(real_in);
        free(real_out);
        return 1;  // TODO CHANGE TO 1
    }

    if (is_str_equal(real_in, real_out)) {
        free(real_in);
        free(real_out);
        return 1;
    }

    free(real_in);
    free(real_out);

    return 0;
}

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

        if (length > 5) {
            destroy_student(&cur);
            return throw_err(INCORRECT_INPUT_DATA);
        }

        append_stud(students, cur);
        read++;

        reset_student(&cur);
    }

    destroy_student(&cur);

    return 0;
}

float student_mean(Student student) {
    float mean = 0;

    for (int i = 0; i < 5; ++i) {
        mean += (float) student.grades[i] / 5.0f;
    }

    return mean;
}

// 0 - By ID, 1 - Name, 2 - Surname, 3 - Group
int student_search(const StudentArr students, int criteria, SearchParameter param, StudentArr *result) {
    double eps = 0.0001;

    for (int i = 0; i < students.length; ++i) {
        Student cur = students.val[i];
        switch (criteria) {
            case 0:
                if (cur.id == param.id)
                    append_stud(result, cur);

                break;
            case 1:
                if (is_arr_equal(cur.name, param.str))
                    append_stud(result, cur);

                break;
            case 2:
                if (is_arr_equal(cur.surname, param.str))
                    append_stud(result, cur);

                break;
            case 3:
                if (is_arr_equal(cur.group, param.str))
                    append_stud(result, cur);

                break;
            case 4:
                if (student_mean(cur) - param.mean > eps)
                    append_stud(result, cur);

                break;
            default:
                return -1;
        }
    }

    return 0;
}

// TODO: add sort and interactive dialog

