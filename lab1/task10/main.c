#include "main.h"

int main() {
    printf("Please enter the base of the values: ");
    int ch;
    seek_char(stdin, &ch);

    Array base_str;
    int err = create_arr(5, &base_str);
    if (err) {
        return err;
    }

    read_value(stdin, &base_str, ch);

    unsigned int base, any = 0;
    arr_to_value(base_str, &base);

    destroy(&base_str);

    if (base < 2 || base > 36)
        return throw_err(INCORRECT_ARGUMENTS);

    Array x;
    err = create_arr(5, &x);
    if (err) {
        return err;
    }

    int res = parse_str(&x);
    long long max = LLONG_MIN;
    while (res == 0) {
        long long dec;
        err = to_decimal(x, base, &dec);
        if (err) {
            destroy(&x);
            return err;
        }
        if (dec > max)
            max = dec;
        res = parse_str(&x);
        any = 1;
    }
    if (res > 0) {
        destroy(&x);
        return res;
    }
    if (!any) {
        destroy(&x);
        return throw_err(INCORRECT_ARGUMENTS);
    }
    to_base(max, 9, &x);
    print_arr(x);
    to_base(max, 18, &x);
    print_arr(x);
    to_base(max, 27, &x);
    print_arr(x);
    to_base(max, 36, &x);
    print_arr(x);
    destroy(&x);

    return 0;
}
