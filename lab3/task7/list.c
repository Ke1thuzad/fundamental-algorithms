#include "main.h"

LiverList* create_node(Liver val) {
    LiverList *new = (LiverList*) malloc(sizeof(LiverList));
    if (!new)
        return NULL;

    new->next = NULL;

    copy_liver(&new->val, &val);

    return new;
}

int prepend_list(LiverList **list, Liver val) {
    LiverList *new = create_node(val);
    if (!new)
        return throw_err(MEMORY_NOT_ALLOCATED);

    new->next = *list;

    *list = new;

    return 0;
}

int append_list(LiverList **list, Liver val) {

    LiverList *new = create_node(val);
    if (!new)
        return throw_err(MEMORY_NOT_ALLOCATED);

    if (*list == NULL) {
        *list = new;
        return 0;
    }

    LiverList *temp = *list;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = new;

    return 1;
}

int append_list_address(LiverList **list, LiverList *val) {
    if (*list == NULL) {
        *list = val;
        return 0;
    }

    LiverList *temp = *list;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = val;

    return 1;
}

int delete_node(LiverList **list, LiverList *addr) {
    LiverList *cur = *list, *prev = cur;
    while (cur) {

        if (cur == addr) {
            if (prev == *list) {
                *list = cur->next;
            } else {
                prev->next = cur->next;
            }

            destroy_liver(&cur->val);
            free(cur);

            return 0;
        }

        cur = cur->next;
        prev = cur;
    }

    *list = cur;

    return 1;
}

int copy_list(LiverList **dst, LiverList *src) {
    LiverList *temp_dst = *dst;
    LiverList *temp_src = src;
    do {
        int err = append_list(&temp_dst, temp_src->val);
        if (err > 1)
            return err;
    } while ((temp_src = temp_src->next));

    *dst = temp_dst;

    return 0;
}

void destroy_list(LiverList **list) {
    LiverList *cur = *list, *prev;

    while (cur) {
        prev = cur;
        cur = cur->next;

        destroy_liver(&prev->val);

        free(prev);
    }

    *list = NULL;
}

void write_livers(FILE *out, LiverList *list) {
    LiverList *cur = list;
    int index = 1;

    fprintf(out, "Liver List:\n");

    while (cur) {
        fprintf(out, "\tLiver %d:\n", index);
        fprintf(out, "\t\tSurname: %s\n", cur->val.surname.val);
        fprintf(out, "\t\tName: %s\n", cur->val.name.val);
        fprintf(out, "\t\tPatronymic: %s\n", cur->val.patronymic.val);
        fprintf(out, "\t\tBirthdate: %s\n", cur->val.birthdate.val);
        fprintf(out, "\t\tSex: %c\n", cur->val.sex);
        fprintf(out, "\t\tMean Salary: %f\n", cur->val.mean_salary);
        fprintf(out, "\n");

        index++;
        cur = cur->next;
    }

    fprintf(out, "\n");
}

int insert_list_condition(LiverList **list, Liver val, int (*cmp)(const void*, const void*)) {
    LiverList *cur = *list, *prev = cur;

    while (cur) {

        if (cmp(&cur->val, &val) >= 0) {
            if (cur == *list) {
                prepend_list(list, val);

                return 0;
            }

            LiverList *new_node = create_node(val);
            if (!new_node)
                return throw_err(MEMORY_NOT_ALLOCATED);

            new_node->next = cur;
            prev->next = new_node;

            return 0;
        }

        prev = cur;
        cur = cur->next;
    }

    append_list(list, val);

    return 0;
}

int copy_liver(Liver *dst, const Liver *src) {
    int err = copy_newstr(&dst->name, &src->name);
    if (err)
        return err;

    err = copy_newstr(&dst->surname, &src->surname);
    if (err)
        return err;

    err = copy_newstr(&dst->patronymic, &src->patronymic);
    if (err)
        return err;

    err = copy_newstr(&dst->birthdate, &src->birthdate);
    if (err)
        return err;

    dst->mean_salary = src->mean_salary;
    dst->sex = src->sex;

    return 0;
}

int liver_equiv(Liver a, Liver b) {
    return equiv_str(a.surname, b.surname) && equiv_str(a.name, b.name) && equiv_str(a.patronymic, b.patronymic) &&
            equiv_str(a.birthdate, b.birthdate) && a.sex == b.sex && (a.mean_salary - b.mean_salary < 0.0000001);
}

int find_liver(LiverList **livers, Liver val, LiverList **result) {
    LiverList *cur = *livers;

    while (cur) {
        if (liver_equiv(cur->val, val)) {
            *result = cur;
            return 0;
        }

        cur = cur->next;
    }

    return 1;
}

int liver_search(LiverList **livers, SearchCriteria criteria, SearchParameter param, LiverList **result, int addresses) {
    double eps = 0.0000001;
    int read = 0;
    int err;

    LiverList *cur = *livers;

    while (cur) {
        switch (criteria) {
            case SURNAME:
                if (equiv_str(cur->val.surname, param.str)) {
                    read++;
                    if (addresses)
                        append_list_address(result, cur);  // TODO: Change it because recursion happens
                    else {
                        err = insert_list_condition(result, cur->val, compare_age);
                        if (err)
                            return err;
                    }
                }

                break;
            case NAME:
                if (equiv_str(cur->val.name, param.str)) {
                    read++;
                    if (addresses)
                        append_list_address(result, cur);
                    else {
                        err = insert_list_condition(result, cur->val, compare_age);
                        if (err)
                            return err;
                    }
                }

                break;
            case PATRONYMIC:
                if (equiv_str(cur->val.patronymic, param.str)) {
                    read++;
                    if (addresses)
                        append_list_address(result, cur);
                    else {
                        err = insert_list_condition(result, cur->val, compare_age);
                        if (err)
                            return err;
                    }
                }

                break;
            case BIRTHDATE:
                if (equiv_str(cur->val.birthdate, param.str)) {
                    read++;
                    if (addresses)
                        append_list_address(result, cur);
                    else {
                        err = insert_list_condition(result, cur->val, compare_age);
                        if (err)
                            return err;
                    }
                }

                break;
            case SEX:
                if (cur->val.sex == param.sex) {
                    read++;
                    if (addresses)
                        append_list_address(result, cur);
                    else {
                        err = insert_list_condition(result, cur->val, compare_age);
                        if (err)
                            return err;
                    }
                }

                break;
            case SALARY:
                if (fabsf(cur->val.mean_salary - param.salary) < eps) {
                    read++;
                    if (addresses)
                        append_list_address(result, cur);
                    else {
                        err = insert_list_condition(result, cur->val, compare_age);
                        if (err)
                            return err;
                    }
                }

                break;
            default:
                return throw_err(INCORRECT_OPTION);
        }

        cur = cur->next;
    }

    return read;
}

int parse_time(const String *str, Time *time) {
    int day, month, year;
    if (sscanf(str->val, "%2d.%2d.%4d", &day, &month, &year) != 3) {
        return 1;
    }

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0) {
        return 1;
    }

    time->day = day;
    time->month = month;
    time->year = year;

    return 0;
}

int parse_time_arr(const Array *str, Time *time) {
    int day, month, year;
    if (sscanf(str->val, "%2d.%2d.%4d", &day, &month, &year) != 3) {
        return 1;
    }

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0) {
        return 1;
    }

    time->day = day;
    time->month = month;
    time->year = year;

    return 0;
}

int compare_time(const void *a, const void *b) {
    Time t1 = *((Time *) a);
    Time t2 = *((Time *) b);

    if (t1.year != t2.year) return t1.year - t2.year;

    if (t1.month != t2.month) return t1.month - t2.month;

    return t1.day - t2.day;
}

int compare_time_str(const void *a, const void *b) {
    String *time1 = (String *) a;
    String *time2 = (String *) b;

    Time t1, t2;
    if (parse_time(time1, &t1) || parse_time(time2, &t2)) {
        return throw_err(INCORRECT_INPUT_DATA);
    }

    return compare_time(&t1, &t2);
}

int compare_age(const void *liver1, const void *liver2) {
    Liver *a = (Liver *) liver1;
    Liver *b = (Liver *) liver2;

    return -compare_time_str(&a->birthdate, &b->birthdate);
}

void destroy_liver(Liver *liver) {
    destroy_str(&liver->name);
    destroy_str(&liver->surname);
    destroy_str(&liver->patronymic);
    destroy_str(&liver->birthdate);
}

