#include "main.h"

int is_str_equal(char* str1, char* str2) {
    while (*str1 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return (*str1 == '\0' && *str2 == '\0');
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

int read_value(FILE* f, Array* result, char first) {
    int err;
    if (first) {
        err = append(result, first);
        if (err)
            return err;
    }
    int character = fgetc(f);
    while (character > ' ') {
        if (!is_num(character))
            return throw_err(INCORRECT_ARGUMENTS);
        err = append(result, (char)character);
        if (err)
            return err;
        character = fgetc(f);
    }

    return 0;
}

int chrtoint(char x, int* num) {
    int a = x - '0';
    if (a < 0 || a > 9) return throw_err(OUT_OF_BOUNDS);
    *num = a;
    return 0;
}

int parse_int(char* str, int* res) {
    int i = 0, result = 0, sign = 1;

    if (str[0] == '-') i++, sign = -1;

    while (str[i] != '\0') {
        int temp, err = chrtoint(str[i], &temp);
        if (err)
            return err;
        result *= 10;
        result += temp;
        i++;
    }

    *res = sign * result;
    return 0;
}

int parse_str(Array* result) {
    if (result)
        destroy(result);

    char temp[5] = {};
    int err, ind = 0;
    err = create_arr(5, result);
    if (err) {
        destroy(result);
        return err;
    }
    int ch = getchar();
    while (ch > ' ') {
        if (!is_alnum(ch))
            return throw_err(INCORRECT_ARGUMENTS);
        char lower = (char) to_lower(ch);
        if (ind < 4)
            temp[ind++] = lower;
        err = append(result, lower);
        if (err) {
            destroy(result);
            return err;
        }
        ch = getchar();
    }
    if (ind == 4) {
        if (is_str_equal(temp, "stop")) {
            destroy(result);
            return -1;
        }
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

int base_char_to_dec(char x) {
    if (is_num(x))
        return x - '0';
    if (is_letter(x))
        return to_lower(x) - 'a' + 10;
    return throw_err(-2);
}

int to_decimal(const Array x, unsigned char base, long long *result) {
    int base_maxes[35] = {63, 40, 32, 28, 25, 23, 21, 20, 19, 19, 18, 18, 17, 17, 16, 16, 16, 15, 15, 15, 15, 14, 14, 14, 14, 14, 14, 13, 13, 13,
                          13, 13, 13, 13, 13};
    if (x.length > base_maxes[base - 2]) {
        return throw_err(OUT_OF_BOUNDS);
    }
    if (base < 2 || base > 36)
        return throw_err(OUT_OF_BOUNDS);

    *result = 0;
    long long pwr = 1;

    for (int i = x.length - 1; i >= 0; --i) {
        int chr = base_char_to_dec(x.val[i]);
        if (chr >= base)
            return throw_err(INCORRECT_ARGUMENTS);
        *result += chr * pwr;
        pwr *= base;
    }
    return 0;
}

// Base 2-36
int to_base(unsigned long long x, unsigned char base, Array * result) {
    if (result)
        destroy(result);

    int err;
    err = create_arr(5, result);
    if (err) {
        return err;
    }

    if (base < 2 || base > 36) {
        return throw_err(OUT_OF_BOUNDS);
    }
    char letters[37] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (x > 0) {
        err = append(result, letters[x % base]);
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