#include "main.h"

int is_str_equal(char *str1, char *str2) {
    while (*str1 && *str1 == *str2++)
        if (*str1++ == '\0') return 1;
    return !*str1 && !*str2;
}


int str_compare(char *str1, char *str2) {
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

char *string_copy(char *dst, const char *src) {
    char *dstaddr = dst;
    while ((*dstaddr++ = *src++));
    return dstaddr;
}

int create_arr(unsigned int length, EmployeeArr *arr) {

    arr->capacity = length;
    arr->length = 0;
    arr->val = (Employee *) malloc(length * sizeof(Employee));


    if (!arr->val) return throw_err(MEMORY_NOT_ALLOCATED);

    return 0;
}

int resize(EmployeeArr *arr, int size_delta) {
    Employee *new_addr = (Employee *) realloc(arr->val, (arr->capacity + size_delta) * sizeof(Employee));

    if (!new_addr) {
        free(arr->val);
        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    arr->val = new_addr;
    arr->capacity += size_delta;
    return 0;
}

int extend(EmployeeArr *arr) {
    return resize(arr, arr->capacity);
}

int append(EmployeeArr *arr, Employee value) {
    if (arr->length >= (arr->capacity - 1)) {
        int err = extend(arr);
        if (err)
            return err;
    }

    char tempname[1024], tempsurname[1024];

    Employee cur = {value.id, "", "", value.salary};
    string_copy(cur.name, value.name);
    string_copy(cur.surname, value.surname);

    arr->val[arr->length++] = cur;
    return 0;
}

void destroy(EmployeeArr *arr) {
    if (arr->val)
        free(arr->val);
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

    if (!is_str_equal(a1->surname, b1->surname)) {
        return -str_compare(a1->surname, b1->surname);
    }

    if (!is_str_equal(a1->name, b1->name)) {
        return -str_compare(a1->name, b1->name);
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

    if (!is_str_equal(a1->surname, b1->surname)) {
        return str_compare(a1->surname, b1->surname);
    }

    if (!is_str_equal(a1->name, b1->name)) {
        return str_compare(a1->name, b1->name);
    }

    return a1->id > b1->id;
}

int GetOpts(int argc, char **argv, option *opt, char **filenames) {
    if (argc != 4)
        return throw_err(INCORRECT_ARGUMENTS);

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

    while (1) {
        read = fscanf(in, "%d %s %s %f\n", &cur.id, cur.name, cur.surname, &cur.salary);
        if (read <= 0)
            break;

        if (read != 4 || cur.name[0] == ' ' || cur.surname[0] == ' ' || cur.salary < 0) {
            return throw_err(INCORRECT_ARGUMENTS);
        }

        append(all, cur);
    }

    return 0;
}

int write_employees(FILE *out, EmployeeArr all) {
    for (int i = 0; i < all.length; ++i) {
        fprintf(out, "ID: %3u | Full name: %s %s | Salary: %f.\n", all.val[i].id, all.val[i].surname, all.val[i].name,
                all.val[i].salary);
    }

    return 0;
}

int handler(char **filenames, const option *opt) {
    FILE *in = fopen(filenames[0], "r");
    if (!in)
        return throw_err(FILE_ERROR);

    EmployeeArr all;

    int err = create_arr(5, &all);
    if (err)
        return err;

    err = read_employees(in, &all);
    if (err)
        return err;


    fclose(in);

    if (*opt == ASCENDING)
        qsort(all.val, all.length, sizeof(Employee), compare_employee_ascending);
    else
        qsort(all.val, all.length, sizeof(Employee), compare_employee_descending);

    FILE *out = fopen(filenames[1], "w");
    if (!out)
        return throw_err(FILE_ERROR);

    write_employees(out, all);

    fclose(out);

    return 0;
}

int main(int argc, char **argv) {
    option opt;

    char *filenames[2] = {};

    GetOpts(argc, argv, &opt, filenames);

    handler(filenames, &opt);

    return 0;
}

