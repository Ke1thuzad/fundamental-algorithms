#include "main.h"

int overfscanf(FILE* stream, const char* format, ...) {
    va_list args;
    va_start(args, format);

    int i = 0, k = 0, err;
    while (format[i]) {
        if (k) {
            char flaga[20];
            i += snread_value(format + i, flaga, 20, '%');
            char* flag = flaga + 1;

            if (is_str_equal(flag, "Ro")) {
                Array arr;
                err = create_arr(5, &arr);
                if (err)
                    return err;

                err = to_roman_numeral(va_arg(args, int), &arr);
                if (err) {
                    destroy(&arr);
                    return err;
                }

                fputs(arr.val, stream);
                destroy(&arr);
            } else if (is_str_equal(flag, "Zr")) {
                IntArray arr;
                err = create_intarr(5, &arr);
                if (err)
                    return err;

                err = to_zeckendorf(va_arg(args, unsigned int), &arr);
                if (err) {
                    destroy_int(&arr);
                    return err;
                }

                for (int j = 0; j < arr.length; ++j) {
                    fprintf(stream, "%d", arr.val[j]);
                    if (j < arr.length - 1)
                        fputc(' ', stream);
                }

                destroy_int(&arr);
            } else if (is_str_equal(flag, "Cv")) {
                Array arr;
                err = create_arr(5, &arr);
                if (err)
                    return err;

                int x = va_arg(args, int), base = va_arg(args, int);

                err = to_base(x, base, &arr, 1);
                if (err) {
                    destroy(&arr);
                    return err;
                }

                fputs(arr.val, stream);
                destroy(&arr);
            } else if (is_str_equal(flag, "CV")) {
                Array arr;
                err = create_arr(5, &arr);
                if (err)
                    return err;

                int x = va_arg(args, int), base = va_arg(args, int);

                err = to_base(x, base, &arr, 0);
                if (err) {
                    destroy(&arr);
                    return err;
                }

                fputs(arr.val, stream);
                destroy(&arr);
            } else if (is_str_equal(flag, "to") || is_str_equal(flag, "TO")) {

                Array arr, inp;
                err = create_arr(5, &arr);
                if (err)
                    return err;

                err = create_arr(5, &inp);
                if (err) {
                    destroy(&arr);
                    return err;
                }
                str_to_arr(va_arg(args, char*), &inp);
                int base = va_arg(args, int);

                int lower = flag[0] == 't' ? 1 : 0;

                err = to_decimal(inp, base, &arr, lower);
                if (err) {
                    destroy(&arr);
                    destroy(&inp);
                    return err;
                }

                fputs(arr.val, stream);
                destroy(&arr);
                destroy(&inp);
            } else if (is_str_equal(flag, "mi")) {
                int val = va_arg(args, int);
                fprint_bits(sizeof(int), &val, stream);
            } else if (is_str_equal(flag, "mu")) {
                unsigned int val = va_arg(args, unsigned int);
                fprint_bits(sizeof(unsigned int), &val, stream);
            } else if (is_str_equal(flag, "md")) {
                double val = va_arg(args, double);
                fprint_bits(sizeof(double), &val, stream);
            } else if (is_str_equal(flag, "mf")) {
                float val = va_arg(args, double);
                fprint_bits(sizeof(float), &val, stream);
            } else {
                vfprintf(stream, flaga, args);
            }

            k = 0;
            continue;
        }

        if (format[i] != '%')
            fputc(format[i], stream);
        else
            k = 1;


        i++;
    }

    va_end(args);

    return 0;
}

int len(const char* str) {
    int i = 0;
    while(str[i++] != '\0');
    return i;
}

void string_concat(char* str1, const char* str2) {
    int i = 0, ln = len(str1) - 1;
    while (str2[i]) {
        str1[ln++] = str2[i++];
    }
    str1[ln] = '\0';
}

int is_str_equal(char* str1, char* str2) {
    while (*str1 && *str1 == *str2++)
        if (*str1++ == '\0') return 1;
    return !*str1 && !*str2;
}

int snread_value(const char* str, char* result, int n, char first) {
    int i = 0, j = 0;
    if (first)
        result[i++] = first;

    char character = str[j++];
    while (character > ' ' && i < n && character != '%') {
        result[i++] = character;
        character = str[j++];
    }
    result[i] = '\0';

    return i - 1;
}

int roman_value(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

int unroman(char *str, int *result) {
    int total = 0;
    int i = 0;
    int prev = 0;

    while (str[i] != '\0') {
        int current_value = roman_value(str[i]);

        total += current_value;

        if (current_value > prev) {
            total -= prev * 2;
        }

        prev = current_value;
        i++;
    }

    *result = total;

    return 0;
}

int zecken(unsigned int *result, ...) {
    va_list args;
    va_start(args, result);

    unzeckendorf(result, args);

    va_end(args);
    return 0;
}

int unzeckendorf(unsigned int *result, va_list args) {
    *result = 0;
    unsigned int prev = 0, cur = 0;
    unsigned int a = 0, b = 1, i = 0;

    while (1) {
        prev = cur;
        cur = va_arg(args, unsigned int);
        if (prev == 1 && prev == cur)
            break;

        if (i % 2) {
            a += b;
            *result += a * cur;
        } else {
            b += a;
            *result += b * cur;
        }

        i++;
    }

    return 0;
}

int to_decimal(const Array x, unsigned char base, int *result) {
//    if (base < 2 || base > 36)
//        return throw_err(INCORRECT_ARGUMENTS);

    *result = 0;
    int pwr = 1;

    for (int i = x.length - 1; i >= 0; --i) {
        int chr = base_char_to_dec(x.val[i]);
//        if (chr >= base)
//            return throw_err(INCORRECT_ARGUMENTS);
        *result += chr * pwr;
        pwr *= base;
    }
    return 0;
}