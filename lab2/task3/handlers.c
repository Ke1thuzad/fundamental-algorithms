#include "main.h"

int len(const char* str) {
    int i = 0;
    while(str[i++] != '\0');
    return i;
}

int substr(const char* str, int n, const char* key, int m) {
    n--;
    m--;
    int table[m], i = 0, j = 0;

    shift_table(key, m, table);

    while (i < n) {
        if (str[i] == key[j]) {
            i++;
            j++;
            if (j == m) {
                return i - j; // First occurrence.
            }
        } else {
            if (j > 0) {
                j = table[j - 1];
            } else {
                i++;
            }
        }

    }
    return -1;
}

// 0 1 2 3 4 5 6 7
// л и и л л и и л
// 0 0 0 1 1 2 3 4
// j - - i

int shift_table(const char *template, int n, int *result) {
    if (n == 0)
        return throw_err(INCORRECT_ARGUMENTS);

    int i = 1, j = 0;
    result[0] = 0;
    while (i < n) {
        if (template[i] != template[j]) {
            if (j == 0) {
                result[i] = 0;
                i++;
            } else if (j > 0) {
                j = result[j - 1];
            }
        } else {
            j++;
            result[i] = j;
            i++;
        }
    }
    return 0;
}

int find_substr_in_files(char* substr, int m, int file_count, ...) {
    va_list files;
    char* filename;

    va_start(files, file_count);
    for (int i = 0; i < file_count; ++i) {
        filename = va_arg(files, char*);
        // TODO: Make search
    }
    va_end(files);

    return 0;
}
