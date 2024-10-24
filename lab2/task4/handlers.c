#include "main.h"

char* string_copy(char *dst, const char *src) {
    char *dstaddr = dst;
    while((*dst++ = *src++));
    return dstaddr;
}

int is_str_equal(char* str1, char* str2) {
    while (*str1 && *str1 == *str2++)
        if (*str1++ == '\0') return 1;
    return !*str1 && !*str2;
}

int is_convex(int n, ...) {
    if (n <= 2)
        return 0;

    if (n < 4)
        return 1;


    va_list vals;
    Point all_points[n], a, b, c;

    va_start(vals, n);
    for (int i = 0; i < n; i++) {
        all_points[i] = va_arg(vals, Point);
    }
    va_end(vals);

    int sign = 0, prev;

    for (int i = 0; i < n; i++) {
        prev = sign;
        if (i < 2)
            a = all_points[n + i - 2], b = all_points[(n + i - 1) % n], c = all_points[i];
        else
            a = all_points[i - 2], b = all_points[i - 1], c = all_points[i];
        double dx1 = b.x - a.x, dy1 = b.y - a.y, dx2 = c.x - b.x, dy2 = c.y - b.y;
        double cross = dx1 * dy2 - dy1 * dx2;
        if (cross <= 0)
            sign = -1;
        else
            sign = 1;
        if (prev == 0)
            continue;
        if (sign != prev)
            return 0;
    }

    return 1;
}

int polynomial(double *result, double point, int n, ...) {
    if (n < 0)
        return throw_err(INCORRECT_ARGUMENTS);

    va_list vals;

    va_start(vals, n);
    *result = va_arg(vals, double);

    for (int i = 0; i < n; ++i) {
        if (i < n - 1)
            *result *= point;
        *result = (*result + va_arg(vals, double));
    }
    va_end(vals);

//    *result += coefficients[n - 1];

    return 0;
}

int kaprekar_handler(int base, int n, ...) {
    if (n < 0 || base < 2 || base > 36)
        return throw_err(INCORRECT_ARGUMENTS);

    va_list vals;

    Array tmp;
    int err = create_arr(5, &tmp);
    if (err)
        return err;

    char* str;

    va_start(vals, n);

    for (int i = 0; i < n; ++i) {
        str = va_arg(vals, char*);
        str_to_arr(str, &tmp);
        if (is_kaprekar(tmp, base)) {
            printf("%s is a Kaprekar number in base %d.\n", tmp.val, base);
        } else {
            printf("%s is not a Kaprekar number in base %d.\n", tmp.val, base);
        }
    }

    va_end(vals);

    destroy(&tmp);

    return 0;
}

int is_kaprekar(Array val, int base) {
    // val ^ 2
//    multiply_arrays();
    Array temp, temp2, temp3, temp4;
    int err = create_arr(5, &temp);
    if (err)
        return err;

    err = create_arr(5, &temp2);
    if (err) {
        destroy(&temp);
        return err;
    }

    err = create_arr(5, &temp3);
    if (err) {
        destroy(&temp);
        destroy(&temp2);
        return err;
    }

    err = create_arr(5, &temp4);
    if (err) {
        destroy(&temp);
        destroy(&temp2);
        destroy(&temp3);
        return err;
    }

    err = multiply_arrays(val, val, base, &temp);
    if (err) {
        destroy(&temp);
        destroy(&temp2);
        destroy(&temp3);
        destroy(&temp4);
        return err;
    }

    int res = 0;

    if (temp.length == 1) {
        copy(&temp2, &temp);
        value_to_arr(0, &temp3);
        add_arrays_base(temp2, temp3, &temp4, base);
        res += is_str_equal(val.val, temp4.val);
    }
    int asd = 0;

    arr_to_value(val, &asd);

    for (int i = 1; i < temp.length; ++i) {
        reset(&temp2);
        reset(&temp3);
        reset(&temp4);

        slice(temp, 0, i, 1, &temp2);
        slice(temp, i, temp.length, 1, &temp3);

        unsigned int arrval = 0;
        arr_to_value(temp2, &arrval);
        if (arrval == 0)
            continue;

        arr_to_value(temp3, &arrval);
        if (arrval == 0)
            continue;

        add_arrays_base(temp2, temp3, &temp4, base);
        res += is_str_equal(val.val, temp4.val);
    }

    destroy(&temp);
    destroy(&temp2);
    destroy(&temp3);
    destroy(&temp4);

    if (res)
        return 1;

    return 0;
}