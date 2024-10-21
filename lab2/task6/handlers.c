#include "main.h"

int overfscanf(FILE* stream, const char* format, ...) {
    va_list args;
    va_start(args, format);

    int i = 0, k = 0, err;
    Array buffer;
    err = create_arr(5, &buffer);
    if (err)
        return err;

    while (format[i]) {
        if (k) {
            long int start_pos = ftell(stream);
//            printf("%ld\n", ftell(stream));
            for (int j = 0; j < buffer.length; ++j) {
                if (buffer.val[j] != fgetc(stream)) {
                    destroy(&buffer);
                    return throw_err(INCORRECT_ARGUMENTS);
                }
            }

//            fseek(stream, start_pos, SEEK_SET);
//            printf("%ld\n", ftell(stream));

            char flaga[20];
            i += snread_value(format + i, flaga, 20, '%');
            char* flag = flaga + 1;

            if (is_str_equal(flag, "Ro")) {
                char roman[100];

                fscanf(stream, "%s", roman);

                int* result = va_arg(args, int*);

                unroman(roman, result);
            } else if (is_str_equal(flag, "Zr")) {
                unsigned int* result = va_arg(args, unsigned int*);

                unzeckendorf(result, stream);
            } else if (is_str_equal(flag, "Cv") || is_str_equal(flag, "CV")) {
                int* result = va_arg(args, int*);
                int base = va_arg(args, int);
                int ch;
                Array input;
                err = create_arr(5, &input);
                if (err) {
                    destroy(&buffer);
                    return err;
                }

                seek_char(stream, &ch);
                read_value(stream, &input, ch);

                to_decimal(input, base, result);
            }
//            else if (is_str_equal(flag, "CV")) {
////                Array arr;
////                err = create_arr(5, &arr);
////                if (err)
////                    return err;
////
////                int x = va_arg(args, int), base = va_arg(args, int);
////
////                err = to_base(x, base, &arr, 0);
////                if (err) {
////                    destroy(&arr);
////                    return err;
////                }
////
////                fputs(arr.val, stream);
////                destroy(&arr);
//            }
            else {
//                concat_str(&buffer, flaga);
                vfscanf(stream, flaga, args);
                va_arg(args, void*);
            }

            k = 0;
            reset(&buffer);
            continue;
        }

        if (format[i] != '%') {
            append(&buffer, format[i]);
        } else {
            k = 1;
        }

        i++;
    }

    va_end(args);

    destroy(&buffer);

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

int read_value(FILE* f, Array* result, char first) {
    int err;
    if (first) {
        err = append(result, first);
        if (err)
            return err;
    }
    int character = fgetc(f);
    while (character > ' ') {
        err = append(result, (char)character);
        if (err)
            return err;
        character = fgetc(f);
    }
    fseek(f, -1, SEEK_CUR);

    return 0;
}

int seek_char(FILE* f, int* result) {
    if (!f)
        return throw_err(FILE_ERROR);

    while(!feof(f)) {
        int cur = fgetc(f);
        if (cur > ' ') {
            *result = cur;
            return 0;
        }
    }
    *result = -1;
    return 0;
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

//int zecken(unsigned int *result, ...) {
//    va_list args;
//    va_start(args, result);
//
//    unzeckendorf(result, args);
//
//    va_end(args);
//    return 0;
//}

int unzeckendorf(unsigned int *result, FILE* stream) {
    *result = 0;
    unsigned int prev = 0, cur = 0;
    unsigned int a = 0, b = 1, i = 0, j = 0;

    while (1) {
        prev = cur;
        if(fscanf(stream, "%d", &cur) == 0)
            return throw_err(INCORRECT_ARGUMENTS);

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