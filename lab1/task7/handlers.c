#include "main.h"

int handler_r(Array* paths) {
    FILE* descriptors[3];
    char* flags[3] = {"r", "r", "w"};
    int err = open_descriptors(paths, flags, descriptors, 3);
    if (err)
        return err;

    int i = 0;

    while(!feof(descriptors[0]) && !feof(descriptors[1])) {
        int character;
        err = seek_char(&descriptors[i], &character);
        if (err) {
            for (int k = 0; k < 3; ++k) {
                fclose(descriptors[k]);
            }
            return err;
        }
        if (character != -1) {
            Array arr;
            err = create_arr(5, &arr);
            if (err) {
                for (int k = 0; k < 3; ++k) {
                    fclose(descriptors[k]);
                }
                return err;
            }
            read_value(&descriptors[i], &arr, (char) character);
            i = (i + 1) % 2;
//            printf("%d ", character);
            fputs(arr.val, descriptors[2]);
            fputc(' ', descriptors[2]);
            destroy(&arr);
        } else
            break;
    }
    for (int j = 0; j < 2; ++j) {
        while(!feof(descriptors[j])) {
            int ch;

            err = seek_char(&descriptors[j], &ch);
            if (err) {
                for (int k = 0; k < 3; ++k) {
                    fclose(descriptors[k]);
                }
                return err;
            }

            if (ch != -1) {
                Array arr;
                err = create_arr(5, &arr);
                if (err) {
                    for (int k = 0; k < 3; ++k) {
                        fclose(descriptors[k]);
                    }
                    return err;
                }
                read_value(&descriptors[i], &arr, (char) ch);
                fputs(arr.val, descriptors[2]);
                fputc(' ', descriptors[2]);
                destroy(&arr);
            }
        }
    }
    for (int j = 0; j < 3; ++j) {
        fclose(descriptors[j]);
    }

    return 0;
}

int handler_a(Array* paths) {
    FILE* descriptors[2];
    char* flags[2] = {"r", "w"};
    int err = open_descriptors(paths, flags, descriptors, 2);
    if (err)
        return err;
    int i = 0;
    while (!feof(descriptors[0])) {
        int ch;
        err = seek_char(&descriptors[0], &ch);
        if (err)
            return err;
        if (ch == -1)
            break;
        Array arr;
        err = create_arr(5, &arr);
        if (err)
            return err;
        read_value(&descriptors[0], &arr, (char) ch);

        i = (i + 1) % 10;
        FILE *out = descriptors[1];
        if (i % 10 == 0) {
            if (!is_letter(ch))
                fputs(arr.val, out);
            else {
                for (int j = 0; j < arr.length; ++j) {
                    char hex[6];
                    err = to_base(to_lower(arr.val[j]), 4, hex, 6);
                    if (err) {
                        destroy(&arr);
                        return err;
                    }
                    fputs(hex, out);
                }
            }
        } else if (i % 2 == 0) {
            for (int j = 0; j < arr.length; ++j) {
                if (!is_letter(arr.val[j])) continue;
                arr.val[j] = (char) to_lower(arr.val[j]);
            }
            fputs(arr.val, out);
        }
        else if (i % 5 == 0)
        {
            for (int j = 0; j < arr.length; ++j)
            {
                char hex[4] = {};
                err = to_base(arr.val[j], 8, hex, 4);
                if (err) {
                    destroy(&arr);
                    return err;
                }
                fputs(hex, out);
            }
        } else
            fputs(arr.val, out);
        fputc(' ', out);
        destroy(&arr);
    }
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
    int err;
    if (first) {
        err = append(result, first);
        if (err)
            return err;
    }
    int character = fgetc(*f);
    while (character > ' ') {
        err = append(result, (char)character);
        if (err)
            return err;
        character = fgetc(*f);
    }

    return 0;
}

// Base 2-36
int to_base(unsigned int x, unsigned char base, char* result, size_t res_size) {
    if (base < 2 || base > 36) {
        return throw_err(OUT_OF_BOUNDS);
    }
    char letters[37] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i = 0;

    while (x > 0) {
        if (i >= res_size - 1)
            return throw_err(OUT_OF_BOUNDS);

        result[i++] = letters[x % base];
        x /= base;
    }
    result[i] = '\0';

    for (int j = 0; j < i / 2; j++) {
        char temp = result[j];
        result[j] = result[i - j - 1];
        result[i - j - 1] = temp;
    }

    return 0;
}

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