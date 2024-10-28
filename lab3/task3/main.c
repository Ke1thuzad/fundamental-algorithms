#include "main.h"

int is_str_equal(char* str1, char* str2) {
    while (*str1 && *str1 == *str2++)
        if (*str1++ == '\0') return 1;
    return !*str1 && !*str2;
}

int create_emparr(unsigned int length, EmployeeArr *arr) {
    arr->capacity = length;
    arr->length = 0;
    arr->val = (Employee *) malloc(length * sizeof(Employee));
    if (!arr->val) return throw_err(MEMORY_NOT_ALLOCATED);
    return 0;
}

int resize_emp(EmployeeArr *arr, int size_delta) {
    Employee *new_addr = (Employee *) realloc(arr->val, (arr->capacity + size_delta) * sizeof(Employee));
    if (!new_addr) {
        free(arr->val);
        return throw_err(MEMORY_NOT_ALLOCATED);
    }
    arr->val = new_addr;
    arr->capacity += size_delta;
    return 0;
}

int extend_emp(EmployeeArr *arr) {
    return resize_emp(arr, arr->capacity);
}

int append_emp(EmployeeArr *arr, Employee value) {
    if (arr->length >= arr->capacity) {
        int err = extend_emp(arr);
        if (err) return err;
    }
    arr->val[arr->length++] = value;
    return 0;
}

void destroy_emp(EmployeeArr *arr) {
    for (int i = 0; i < arr->length; ++i) {
        destroy(&arr->val[i].name);
        destroy(&arr->val[i].surname);
    }
    if (arr->val) free(arr->val);
    arr->val = NULL;
    arr->length = 0;
    arr->capacity = 0;
}

int compare_employee_descending(const void *a, const void *b) {
    Employee *a1 = (Employee *) a;
    Employee *b1 = (Employee *) b;

    double eps = 0.00001;

    if (fabsf(a1->salary - b1->salary) >= eps) {
        return a1->salary - b1->salary < eps;
    }

    if (!is_arr_equal(a1->surname, b1->surname)) {
        return -arr_compare(a1->surname, b1->surname);
    }

    if (!is_arr_equal(a1->name, b1->name)) {
        return -arr_compare(a1->name, b1->name);
    }

    return a1->id < b1->id;
}

int compare_employee_ascending(const void *a, const void *b) {
    Employee *a1 = (Employee *) a;
    Employee *b1 = (Employee *) b;

    double eps = 0.00001;

    if (fabsf(a1->salary - b1->salary) >= eps) {
        return a1->salary - b1->salary > eps;
    }

    if (!is_arr_equal(a1->surname, b1->surname)) {
        return arr_compare(a1->surname, b1->surname);
    }

    if (!is_arr_equal(a1->name, b1->name)) {
        return arr_compare(a1->name, b1->name);
    }

    return a1->id > b1->id;
}

int GetOpts(int argc, char **argv, option *opt, char **filenames) {
    if (argc != 4) return throw_err(INCORRECT_ARGUMENTS);

    int findex = 0;

    for (int i = 1; i <= 3; ++i) {
        char *proceeding_option = argv[i];
        if ((proceeding_option[0] == '/' || proceeding_option[0] == '-') && !proceeding_option[2]) {
            switch (proceeding_option[1]) {
                case 'a':
                    *opt = ASCENDING;
                    break;
                case 'd':
                    *opt = DESCENDING;
                    break;
                default:
                    return throw_err(INCORRECT_OPTION);
            }
        } else {
            filenames[findex++] = proceeding_option;
        }
    }
    return 0;
}

int read_employees(FILE *in, EmployeeArr *all) {
    Employee cur = {};
    int read = 1;
    int ch;

    while (1) {
        int err = create_arr(5, &cur.name);
        if (err) return err;

        err = create_arr(5, &cur.surname);
        if (err) {
            destroy(&cur.name);
            return err;
        }

        read = fscanf(in, "%u", &cur.id);
        if (read == -1)
            break;

        err = seek_char(&in, &ch);
        if (ch == -1)
            break;

        if (err || !is_letter(ch)) {
            destroy(&cur.name);
            destroy(&cur.surname);
            return throw_err(INCORRECT_ARGUMENTS);
        }

        err = read_value(&in, &cur.name, ch);
        if (err) {
            destroy(&cur.name);
            destroy(&cur.surname);
            return err;
        }
        read++;

        err = seek_char(&in, &ch);
        if (err || !is_letter(ch)) {
            destroy(&cur.name);
            destroy(&cur.surname);
            return throw_err(INCORRECT_ARGUMENTS);
        }

        err = read_value(&in, &cur.surname, ch);
        if (err) {
            destroy(&cur.name);
            destroy(&cur.surname);
            return err;
        }
        read++;

        read += fscanf(in, "%f\n", &cur.salary);
        if (read <= 0)
            break;

        if (read != 4 || cur.salary < 0) {
            destroy(&cur.name);
            destroy(&cur.surname);
            return throw_err(INCORRECT_ARGUMENTS);
        }

        append_emp(all, cur);
    }

    destroy(&cur.name);
    destroy(&cur.surname);

    if (!feof(in)) return throw_err(INCORRECT_ARGUMENTS);

    return 0;
}

int write_employees(FILE *out, EmployeeArr all) {
    for (int i = 0; i < all.length; ++i) {
        fprintf(out, "ID: %3u | Full name: %s %s | Salary: %f.\n", all.val[i].id, all.val[i].surname.val,
                all.val[i].name.val, all.val[i].salary);
    }

    return 0;
}

int handler(char **filenames, const option *opt) {
    FILE *in = fopen(filenames[0], "r");
    if (!in) return throw_err(FILE_ERROR);

    EmployeeArr all;

    int err = create_emparr(5, &all);
    if (err) return err;

    err = read_employees(in, &all);
    if (err) {
        destroy_emp(&all);
        return err;
    }

    fclose(in);

    if (*opt == ASCENDING)
        qsort(all.val, all.length, sizeof(Employee), compare_employee_ascending);
    else
        qsort(all.val, all.length, sizeof(Employee), compare_employee_descending);

    FILE *out = fopen(filenames[1], "w");
    if (!out) {
        destroy_emp(&all);
        return throw_err(FILE_ERROR);
    }

    write_employees(out, all);

    destroy_emp(&all);

    fclose(out);

    return 0;
}

int main(int argc, char **argv) {
    option opt;

    char *filenames[2] = {};

    int err = GetOpts(argc, argv, &opt, filenames);
    if (err) return err;

    char *realnames[2] = {};

    realnames[0] = realpath(filenames[0], NULL);
    realnames[1] = realpath(filenames[1], NULL);

    if (is_str_equal(realnames[0], realnames[1])) {
        free(realnames[0]);
        free(realnames[1]);
        return throw_err(INCORRECT_ARGUMENTS);
    }

    free(realnames[0]);
    free(realnames[1]);

    err = handler(filenames, &opt);

    return err;
}
