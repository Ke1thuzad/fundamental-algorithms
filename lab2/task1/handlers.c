#include "main.h"

int parse_uint32(char* str, unsigned int* result) {
    if (!str)
        return throw_err(INCORRECT_ARGUMENTS);
    unsigned int i = 0;
    *result = 0;

    while(str[i] != '\0') {
        if (!is_num(str[i]))
            return throw_err(INCORRECT_ARGUMENTS);
        *result *= 10;
        *result += str[i++] - '0';
    }

    return 0;
}

int to_upper(int x) {
    if (x >= 'a' && x <= 'z')
        return x + ('A' - 'a');
    return x;
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

int handler_l(int argc, char **argv, Array *result) {
    Array str;
    create_arr(5, &str);
    str_to_arr(argv[0], &str);
    unsigned int length = str.length;
    while (length > 0) {
        append(result, length % 10 + '0');
        length /= 10;
    }
    destroy(&str);
    reverse(result);
    return 0;
}

int handler_r(int argc, char** argv, Array *result) {
    Array str;
    create_arr(5, &str);
    str_to_arr(argv[0], &str);

    reverse(&str);
    copy(result, &str);

    destroy(&str);
    return 0;
}

int handler_u(int argc, char** argv, Array *result) {
    Array str;
    create_arr(5, &str);
    str_to_arr(argv[0], &str);

    for (int i = 0; i < str.length; ++i) {
        char ch = str.val[i];
        if (i % 2) {
            ch = (char) to_upper(ch);
        }
        append(result, ch);
    }

    destroy(&str);
    return 0;
}

int handler_n(int argc, char** argv, Array *result) {
    Array str;
    create_arr(5, &str);
    str_to_arr(argv[0], &str);

    for (int i = 0; i < str.length; ++i) {
        if (is_num(str.val[i]))
            append(result, str.val[i]);
    }

    for (int i = 0; i < str.length; ++i) {
        if (is_letter(str.val[i]))
            append(result, str.val[i]);
    }

    for (int i = 0; i < str.length; ++i) {
        if (!is_alnum(str.val[i]))
            append(result, str.val[i]);
    }

    destroy(&str);
    return 0;
}

int handler_c(int argc, char **argv, Array *result) {
    Array str;
    int err = create_arr(5, &str);
    if (err)
        return err;
    str_to_arr(argv[0], &str);

    err = copy(result, &str);
    destroy(&str);
    if (err)
        return err;


    unsigned int count, amount = argc - 4;
    err = parse_uint32(argv[1], &count);
    if (err)
        return err;
//    if (argv[count + 2] || !argv[count + 1])
//        return throw_err(INCORRECT_ARGUMENTS);


    srand(count);

    int str_list[amount] = {}, rnd;

    for (int i = 4; i < argc; ++i) {
        rnd = rand() % amount;
        while (str_list[rnd]) {
            rnd = rand() % amount;
        }
        str_list[rnd] = 1;
        err = concat_str(result, argv[2 + rnd]);
        if (err)
            return err;
    }

    return 0;
}