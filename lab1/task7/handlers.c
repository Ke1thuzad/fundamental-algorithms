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
        if (err)
            return err;
        if (character != -1) {
            i = (i + 1) % 2;
            printf("%d ", character);
            fputc(character, descriptors[2]);
            fputc(' ', descriptors[2]);
        } else
            break;
    }
    for (int j = 0; j < 2; ++j) {
        while(!feof(descriptors[j])) {
            int ch;

            err = seek_char(&descriptors[j], &ch);
            if (err)
                return err;

            printf("%d ", ch);
            if (ch != -1) {
                fputc(ch, descriptors[2]);
                fputc(' ', descriptors[2]);
            }
        }
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

        i = (i + 1) % 11;
        FILE *out = descriptors[1];
        if (i % 10 == 0) {
            if (!is_letter(ch))
                fputc(ch, out);
            else {
                char hex[6];
                err = to_base(to_lower(ch), 4, hex, 6);
                if (err)
                    return err;
                fputs(hex, out);
            }
        } else if (i % 2 == 0) {
            if (!is_letter(ch))
                fputc(ch, out);
            else
                fputc(to_lower(ch), out);
        } else if (i % 5 == 0) {
            char hex[4];
            err = to_base(to_lower(ch), 8, hex, 4);
            if (err)
                return err;
            fputs(hex, out);
        } else
            fputc(ch, out);
        fputc(' ', out);
    }

    return 0;
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