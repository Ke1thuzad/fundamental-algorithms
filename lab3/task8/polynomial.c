#include "main.h"

List* create_node(int val) {
    List *new = (List*) malloc(sizeof(List));
    if (!new)
        return NULL;

    new->next = NULL;
    new->val = val;

    return new;
}

int prepend_list(List **list, int val) {
    List *new = create_node(val);
    if (!new)
        return throw_err(MEMORY_NOT_ALLOCATED);

    new->next = *list;

    *list = new;

    return 0;
}

int append_list(List **list, int val) {

    List *new = create_node(val);
    if (!new)
        return throw_err(MEMORY_NOT_ALLOCATED);

    if (*list == NULL) {
        *list = new;
        return 0;
    }

    List *temp = *list;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = new;

    return 1;
}

int delete_node(List **list, List *addr) {
    List *cur = *list, *prev = cur;
    while (cur) {

        if (cur == addr) {
            if (prev == *list) {
                *list = cur->next;
            } else {
                prev->next = cur->next;
            }
            free(cur);
            return 0;
        }

        cur = cur->next;
        prev = cur;
    }

    *list = cur;

    return 1;
}

int copy_list(List **dst, List *src) {
    List *temp_dst = *dst;
    List *temp_src = src;
    do {
        int err = append_list(&temp_dst, temp_src->val);
        if (err > 1)
            return err;
    } while ((temp_src = temp_src->next));

    *dst = temp_dst;

    return 0;
}

int prepend_polynomial(Polynomial *head, int val) {
    int err = prepend_list(&head->head, val);

    head->n++;

    return err;
}

int append_polynomial(Polynomial *head, int val) {
    int err = append_list(&head->head, val);

    if (err == 1)
        head->n++;

    return err > 1;
}

int search_polynomial_power(Polynomial *a, int val, int power, int max_power) {
    List *cur = a->head, *prev;

    int err;
    int cur_power = max_power;

    if (power > cur_power) {
        for (int i = power - 1; i > cur_power; --i) {
            err = prepend_polynomial(a, 0);
            if (err)
                return err;
        }
        err = prepend_polynomial(a, val);
        if (err)
            return err;
        return 1;
    }

    if (cur_power == power) {
        err = prepend_polynomial(a, val);
        if (err)
            return err;
        return 1;
    }

    while (cur && cur_power != power) {
        prev = cur;
        cur_power--;
        cur = cur->next;
    }

    if (!cur && cur_power != power) {
        for (int i = cur_power; i > power; --i) {
            err = append_polynomial(a, 0);
            if (err)
                return err;
        }
    } else if (cur && cur_power == power) {
        List *temp = create_node(val);

        if (!temp)
            return throw_err(MEMORY_NOT_ALLOCATED);

        temp->next = cur->next;
        free(cur);
        prev->next = temp;

        return 1;
    }

    return 0;
}

void print_polynomial(Polynomial head) {
    List *cur = head.head;
    int power = head.n;
    int flag = 0;

    while (cur != NULL) {
        if (cur->val == 0) {
            if (cur->next != NULL && cur->next->val > 0)
                printf("+");

            cur = cur->next;
            power--;
            continue;
        }

        if (cur->val == -1 && power != 0) {
            printf("-");
        } else if (cur->val != 1 || power == 0) {
            printf("%d", cur->val);
        }

        if (power != 0) {
            printf("x");
            if (power != 1)
                printf("^%d", power);
        }

        if (cur->next != NULL && cur->next->val > 0)
            printf("+");

        cur = cur->next;
        power--;
        flag = 1;
    }
    if (!flag)
        printf("0");

    printf("\n");
}

void destroy_polynomial(Polynomial *head) {
    List *cur = head->head, *prev;
    while (cur != NULL) {
        prev = cur;
        cur = cur->next;
        free(prev);
    }

    head->n = 0;
    head->head = NULL;
}

void destroy_list(List **head) {
    List *cur = *head, *prev;
    while (cur != NULL) {
        prev = cur;
        cur = cur->next;
        free(prev);
    }

    *head = NULL;
}

int copy_polynomial(Polynomial *dst, Polynomial src) {
    if (src.head == NULL && src.n == 0) {
        append_polynomial(dst, 0);
        return 0;
    }

    dst->n = src.n;
    int err = copy_list(&dst->head, src.head);

    return err;
}

int add_polynomials(Polynomial a, Polynomial b, Polynomial *res) {
    int power_a = a.n, power_b = b.n, err;
    List *cur_a = a.head, *cur_b = b.head;

    while (cur_a && cur_b) {
        if (power_a > power_b) {
            err = append_polynomial(res, cur_a->val);
            if (err)
                return err;

            cur_a = cur_a->next;
            power_a--;
        } else if (power_b > power_a) {
            err = append_polynomial(res, cur_b->val);
            if (err)
                return err;

            cur_b = cur_b->next;
            power_b--;
        } else {
            err = append_polynomial(res, cur_a->val + cur_b->val);
            if (err)
                return err;

            cur_a = cur_a->next;
            cur_b = cur_b->next;
            power_a--;
            power_b--;
        }
    }

    return 0;
}

void inverse_polynomial(Polynomial *a) {
    List *cur = a->head;
    do {
        cur->val *= -1;
    } while ((cur = cur->next));
}

int subtract_polynomials(Polynomial a, Polynomial b, Polynomial *res) {
    Polynomial temp = {};
    copy_polynomial(&temp, b);

    inverse_polynomial(&temp);

    int err = add_polynomials(a, temp, res);

    destroy_polynomial(&temp);

    return err;
}

int inplace_decorator(Polynomial *a, Polynomial b, int (*f)(Polynomial a, Polynomial b, Polynomial *res)) {
    Polynomial temp = {};
    int err = copy_polynomial(&temp, *a);
    if (err) {
        destroy_polynomial(&temp);
        return err;
    }

    destroy_polynomial(a);

    err = f(temp, b, a);
    if (err) {
        destroy_polynomial(&temp);
        return err;
    }

    List *cur = a->head;
    while (a->n > 0 && cur && !cur->val) {
        delete_node(&a->head, cur);
        a->n--;
        cur = a->head;
    }

    destroy_polynomial(&temp);

    return 0;
}

int multiply_coefficient_power(Polynomial a, int coefficient, int power, Polynomial *res) {
    List *cur = a.head;
    if (cur == NULL) {
        int err = append_polynomial(res, 0);

        return err;
    }

    if (coefficient == 0) {
        int err = append_polynomial(res, 0);

        return err;
    }

    do {
        int err = append_polynomial(res, cur->val * coefficient);
        if (err)
            return err;
    } while ((cur = cur->next));

    for (int i = 0; i < power; ++i) {
        append_polynomial(res, 0);
    }

    return 0;
}

int multiply_polynomials(Polynomial a, Polynomial b, Polynomial *res) {
    int power_a = a.n, err;

    List *cur_a = a.head;

    while (cur_a) {
        Polynomial b_copy = {};
        err = multiply_coefficient_power(b, cur_a->val, power_a, &b_copy);
        if (err)
            return err;

        err = inplace_decorator(res, b_copy, add_polynomials);
        if (err)
            return err;

        destroy_polynomial(&b_copy);

        cur_a = cur_a->next;
        power_a--;
    }

    return 0;
}

int complete_division(Polynomial a, Polynomial b, Polynomial *quotient, Polynomial *remainder) {
    int err = copy_polynomial(remainder, a);
    if (err)
        return err;

    int power_b = b.n;

    if (b.head == NULL)
        return throw_err(DIVISION_BY_ZERO);

    while (remainder->n >= power_b) {
        int coefficient = remainder->head->val / b.head->val;
        int power_diff = remainder->n - b.n;

        Polynomial term = {};
        err = multiply_coefficient_power(b, coefficient, power_diff, &term);
        if (err)
            return err;

        Polynomial temp = {}, temp2 = {};
        append_polynomial(&temp, 1);
        multiply_coefficient_power(temp, coefficient, power_diff, &temp2);

        err = inplace_decorator(quotient, temp2, add_polynomials);
        if (err) {
            destroy_polynomial(&temp);
            destroy_polynomial(&temp2);
            return err;
        }

        destroy_polynomial(&temp);
        destroy_polynomial(&temp2);

        err = inplace_decorator(remainder, term, subtract_polynomials);
        if (err) {
            destroy_polynomial(&term);
            return err;
        }

        destroy_polynomial(&term);

        if (remainder->n == 0 && remainder->head->val == 0)
            break;
    }

    return 0;
}

int divide_polynomials(Polynomial a, Polynomial b, Polynomial *res) {
    Polynomial remainder = {};

    int err = complete_division(a, b, res, &remainder);

    destroy_polynomial(&remainder);

    return err;
}

int modulus_polynomials(Polynomial a, Polynomial b, Polynomial *res) {
    Polynomial quotient = {};

    int err = complete_division(a, b, &quotient, res);

    destroy_polynomial(&quotient);

    return err;
}

int evaluate_point(Polynomial a, int point) {
    List *cur = a.head;
    int result = 0;

    while (cur) {
        result *= point;
        result = result + cur->val;

        cur = cur->next;
    }

    return result;
}

int derive_polynomial(Polynomial a, Polynomial *res) {
    if (res == NULL)
        return throw_err(INCORRECT_ARGUMENTS);

    int power = a.n;

    List *cur = a.head;
    while (cur) {
        int new_coefficient = cur->val * power;
        int new_power = power - 1;

        if (new_power >= 0) {
            int err = append_polynomial(res, new_coefficient);
            if (err)
                return err;
        }

        cur = cur->next;
        power--;
    }

    return 0;
}

int compose_polynomials(Polynomial a, Polynomial b, Polynomial *res) {
    int power_a = a.n;

    int err;

    List *cur_a = a.head;

    while (cur_a) {

        Polynomial temp = {};

        if (power_a == 0) {
            append_polynomial(&temp, cur_a->val);

            err = inplace_decorator(res, temp, add_polynomials);
            if (err) {
                destroy_polynomial(&temp);
                return err;
            }

            destroy_polynomial(&temp);

            power_a--;
            cur_a = cur_a->next;
            continue;
        }

        copy_polynomial(&temp, b);
        for (int i = 1; i < power_a; ++i) {
            err = inplace_decorator(&temp, b, multiply_polynomials);
            if (err) {
                destroy_polynomial(&temp);
                return err;
            }
        }
        Polynomial term = {};

        multiply_coefficient_power(temp, cur_a->val, 0, &term);

        err = inplace_decorator(res, term, add_polynomials);
        if (err) {
            destroy_polynomial(&term);
            return err;
        }

        destroy_polynomial(&term);
        destroy_polynomial(&temp);

        power_a--;
        cur_a = cur_a->next;
    }

//    Polynomial term = {};
//    append_polynomial(&term, cur_a->val);
//
//    err = inplace_decorator(res, term, add_polynomials);
//    if (err) {
//        destroy_polynomial(&term);
//        return err;
//    }
//
//    destroy_polynomial(&term);


    return 0;
}







