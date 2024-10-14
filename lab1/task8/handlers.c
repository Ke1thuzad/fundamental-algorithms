#include "main.h"

int handler(Array* paths) {
    FILE* descriptors[2];
    char* flags[2] = {"r", "w"};
    int err = open_descriptors(paths, flags, descriptors, 2);
    if (err)
        return err;
    int i = 0;
    FILE* in = descriptors[0], *out = descriptors[1];
    while (!feof(in)) {
        int ch;
        seek_char(&in, &ch);
        if (ch == -1)
            break;

        if (!is_alnum(ch))
            return throw_err(INCORRECT_ARGUMENTS);

        Array val;
        err = create_arr(2, &val);
        if (err)
            return err;
        err = read_value(&in, &val, ch);
        if (err)
            return err;
        fprintf(out, "%s\n", val.val);
        destroy(&val);
    }
    fclose(in);
    fclose(out);
    return 0;
}

int is_alnum(int x) {
    return is_num(x) || is_letter(x);
}

int is_num(int x) {
    return x >= '0' && x <= '9';
}

int is_letter(int x) {
    return x >= 'A' && x <= 'Z' || x >= 'a' && x <= 'z';
}

int to_lower(int x) {
    if (x >= 'A' && x <= 'Z')
        return x + ('a' - 'A');
    return x;
}

int open_descriptors(Array* paths, char** flags, FILE** descriptors, int size) {
    for (int i = 0; i < size; ++i) {
        descriptors[i] = fopen(paths[i].val, flags[i]);
        if (!descriptors[i]){
            for (int j = 0; j < i; ++j) {
                fclose(descriptors[j]);
            }
            return throw_err(FILE_ERROR);
        }
    }
    return 0;
}

int seek_char(FILE** f, int* result) {
    if (!f)
        return throw_err(FILE_ERROR);

    while(!feof(*f)) {
        int cur = fgetc(*f);
        if (cur > ' ') {
            *result = cur;
            return 0;
        }
    }
    *result = -1;
    return 0;
}

int read_value(FILE** f, Array* result, char first) {
    Array arr;
    int err = create_arr(2, &arr);
    if (err) {
        destroy(&arr);
        return err;
    }
    if (first)
        append(&arr, first);

    int character = fgetc(*f), max = 0, cur = 0;
    while (is_alnum(character)) {
        append(&arr, (char)character);
        cur = base_char_to_dec((char)character);
        if (cur > max)
            max = cur;
        character = fgetc(*f);
    }
    if (character > ' ') {
        destroy(&arr);
        return throw_err(INCORRECT_ARGUMENTS);
    }

    err = to_decimal(arr, max + 1, result);

    destroy(&arr);
    if (err)
        return err;

    return 0;
}

int base_char_to_dec(char x) {
    if (is_num(x))
        return x - '0';
    if (is_letter(x))
        return to_lower(x) - 'a' + 10;
    return throw_err(-2);
}

// Base 2-36
int to_decimal(const Array x, unsigned char base, Array *result) {
    if (base < 2 || base > 36)
        return throw_err(OUT_OF_BOUNDS);
    printf("%d ", base);
//    if (result)
//        destroy(result);
    int ind = 0;
    Array* deleteOnExit[5];

//    int err;
//    err = create_arr(5, result);
//    if (err) {
//        destroy(result);
//        return err;
//    }
//    deleteOnExit[ind++] = result;

    Array* pwr = (Array*)malloc(sizeof(Array));
    if(!pwr) {
//        free(deleteOnExit);
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
        int ch = base_char_to_dec(x.val[i]);
        err = multiply(*pwr, ch, 0, &temp);
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

        err = multiply(*pwr, base, 0, &temp);
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
    reverse(result);
    return 0;
}

//int convert_base(Array* x, int from_base, int to_base, Array* result) {
//    printf("%d\n", from_base);
//    if (from_base < 2 || from_base > 36 || to_base < 2 || to_base > 36) {
//        return throw_err(OUT_OF_BOUNDS);
//    }
//    char letters[37] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//
//    long long decimal_value = 0;
//    long long power = 1;
//    for (int i = x->length - 1; i >= 0; --i) {
//        int digit = base_char_to_dec(x->val[i]);
//        if (digit < 0 || digit >= from_base) {
//            return throw_err(INCORRECT_ARGUMENTS);
//        }
//        decimal_value += digit * power;
//        power *= from_base;
//    }
//
//    destroy(result);
//    int err = create_arr(10, result);
//    if (err) {
//        return err;
//    }
//
//    if (decimal_value == 0) {
//        append(result, '0');
//        return 0;
//    }
//
//    while (decimal_value > 0) {
//        int remainder = decimal_value % to_base;
//        char digit_char = letters[remainder];
//        if (digit_char == '\0') {
//            return throw_err(INCORRECT_ARGUMENTS);
//        }
//        err = append(result, digit_char);
//        if (err) {
//            return err;
//        }
//        decimal_value /= to_base;
//    }
//
//    reverse(result);
//
//    return 0;
//}

int is_unique(const Array* arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (is_str_equal(arr[i].val, arr[j].val))
                return 0;
        }
    }

    return 1;
}

int is_str_equal(char* str1, char* str2) {
    while (*str1 && *str1 == *str2++)
        if (*str1++ == '\0') return 1;
    return !*str1 && !*str2;
}