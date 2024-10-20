#include "main.h"

int overfprintf(FILE* stream, const char* format, ...) {
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

int oversprintf(char* buf, const char* format, ...) {
    buf[0] = '\0';
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

                string_concat(buf, arr.val);
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
                    sprintf(buf + len(buf) - 1, "%d", arr.val[j]);
                    if (j < arr.length - 1)
                        sprintf(buf + len(buf) - 1, " ");
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

                string_concat(buf, arr.val);
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

                string_concat(buf, arr.val);
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

                string_concat(buf, arr.val);
                destroy(&arr);
                destroy(&inp);
            } else if (is_str_equal(flag, "mi")) {
                int val = va_arg(args, int);
                sprint_bits(sizeof(int), &val, buf + len(buf) - 1);
            } else if (is_str_equal(flag, "mu")) {
                unsigned int val = va_arg(args, unsigned int);
                sprint_bits(sizeof(unsigned int), &val, buf + len(buf) - 1);
            } else if (is_str_equal(flag, "md")) {
                double val = va_arg(args, double);
                sprint_bits(sizeof(double), &val, buf + len(buf) - 1);
            } else if (is_str_equal(flag, "mf")) {
                float val = va_arg(args, double);
                sprint_bits(sizeof(float), &val, buf + len(buf) - 1);
            } else {
                vsprintf(buf + len(buf) - 1, flaga, args);
            }

            k = 0;
            continue;
        }

        if (format[i] != '%') {
            sprintf(buf + len(buf) - 1, "%c", format[i]);
//            string_concat(buf, &format[i]);
        }
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

int to_roman_numeral(int a, Array* result) {
    if (a < 1)
        return 0;
    int err;
    char roman_numerals[] = "IVXLCDM";
    int numeral_values[] = {1, 5, 10, 50, 100, 500, 1000};
    for (int i = 6; i >= 0; --i) {
        int div = a / numeral_values[i];
        if (div > 0) {
            int rem = a % numeral_values[i];
            if (i % 2 && a / numeral_values[i - 1] == 9) {
                err = append(result, roman_numerals[i - 1]);
                if (err)
                    return err;

                err = append(result, roman_numerals[i + 1]);
                if (err)
                    return err;

                rem = a % numeral_values[i - 1];
            } else if (i % 2 == 0 && div == 4) {
                err = append(result, roman_numerals[i]);
                if (err)
                    return err;

                err = append(result, roman_numerals[i + 1]);
                if (err)
                    return err;
            } else {
                for (int j = 0; j < div; ++j) {
                    err = append(result, roman_numerals[i]);
                    if (err)
                        return err;
                }
            }
            err = to_roman_numeral(rem, result);
            if (err)
                return err;
            break;
        }
    }
    return 0;
}

int to_zeckendorf(unsigned int a, IntArray* result) {
    unsigned int nxt;

    IntArray fibs;
    int err = create_intarr(5, &fibs);
    if (err)
        return err;

    if (max_fib(a, &fibs))
        return throw_err(INCORRECT_ARGUMENTS);

    a -= fibs.val[fibs.length - 1];
    append_int(result, 1);

    for (int i = fibs.length - 2; i > 0; --i) {
        if (a <= 0) {
            err = append_int(result,  0);
            if (err)
                return err;
            continue;
        }

        nxt = fibs.val[i];
        if (a >= nxt) {
            a -= nxt;
            err = append_int(result, 1);
            if (err)
                return err;
        }
        else {
            err = append_int(result,  0);
            if (err)
                return err;
        }
    }
    append_int(result, 0);
    reverse_int(result);
    append_int(result, 1);

    return 0;
}

int max_fib(unsigned int n, IntArray *values) {
    if (n < 1)
        return 1;

    int a = 1, b = 1, i = 0;
    append_int(values, 1);
    append_int(values, 1);
    while (1) {
        if (i % 2 == 0) {
            b += a;
            append_int(values, b);
        }
        else {
            a += b;
            append_int(values, a);
        }
        i++;
        if (a >= n || b >= n) {
            if (a > n || b > n)
                values->val[--values->length] = 0;

            break;
        }
    }

    return 0;
}

// Base 2-36

int to_base(int x, unsigned char base, Array * result, int lower) {
    if (base < 2 || base > 36) {
        value_to_arr(x, result);
        return 0;
    }

    char letters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz";
    lower *= 36;

    int err;

    while (x > 0) {
        err = append(result, letters[x % base + lower]);
        if (err) {
            return err;
        }
        x /= base;
    }

    err = reverse(result);
    if (err) {
        return err;
    }

    return 0;
}

int to_decimal(Array x, unsigned char base, Array *result, int lower) {
    if (base < 2 || base > 36)
        base = 10;

    int ind = 0;
    Array* deleteOnExit[5];

    Array* pwr = (Array*)malloc(sizeof(Array));
    if(!pwr) {
        return throw_err(MEMORY_NOT_ALLOCATED);
    }
    int err = create_arr(5, pwr);
    if (err) {
        free(pwr);
        return err;
    }
    append(pwr, '1');
    deleteOnExit[ind++] = pwr;

    Array temp;
    Array temp2;
    err = create_arr(5, &temp2);
    err |= create_arr(5, &temp);
    if (err) {
        for (int j = 0; j < ind; ++j) {
            if (deleteOnExit[j])
                destroy(deleteOnExit[j]);
        }
        free(pwr);
        return err;
    }

    deleteOnExit[ind++] = &temp;
    deleteOnExit[ind++] = &temp2;

    reverse(&x);

    for (int i = 0; i < x.length; ++i) {
        if (lower) {
            if (x.val[i] < 'a' || x.val[i] > 'z') {
                return throw_err(INCORRECT_ARGUMENTS);
            }
        }
        int ch = base_char_to_dec(x.val[i]);
        err = multiply(*pwr, ch, 10, &temp);
        if (err) {
            for (int j = 0; j < ind; ++j) {
                if (deleteOnExit[j])
                    destroy(deleteOnExit[j]);
            }
            free(pwr);
            return err;
        }

        err = add_arrays(temp2, temp, result);
        if (err) {
            for (int j = 0; j < ind; ++j) {
                if (deleteOnExit[j])
                    destroy(deleteOnExit[j]);
            }
            free(pwr);
            return err;
        }

        err = copy(&temp2, result);
        if (err) {
            for (int j = 0; j < ind; ++j) {
                if (deleteOnExit[j])
                    destroy(deleteOnExit[j]);
            }
            free(pwr);
            return err;
        }

        err = multiply(*pwr, base, 10, &temp);
        if (err) {
            for (int j = 0; j < ind; ++j) {
                if (deleteOnExit[j])
                    destroy(deleteOnExit[j]);
            }
            free(pwr);
            return err;
        }
        err = copy(pwr, &temp);
        if (err) {
            for (int j = 0; j < ind; ++j) {
                if (deleteOnExit[j])
                    destroy(deleteOnExit[j]);
            }
            free(pwr);
            return err;
        }
    }
    for (int j = 0; j < ind; ++j) {
        if (deleteOnExit[j])
            destroy(deleteOnExit[j]);
    }
    free(pwr);
    return 0;
}

void fprint_bits(size_t const size, void const *const ptr, FILE *stream) {
    unsigned char* b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i = size - 1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            fprintf(stream, "%u", byte);
        }
        if (i > 0) {
            fputc(' ', stream);
        }
    }
}

void sprint_bits(size_t const size, void const *const ptr, char *buf) {
    unsigned char* b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i = size - 1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            char buffer[2];
            sprintf(buffer, "%u", byte);
            string_concat(buf, buffer);
        }
        if (i > 0) {
            string_concat(buf, " ");
        }
    }
}