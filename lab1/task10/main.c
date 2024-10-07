#include "main.h"

int main() {
    char base_str[3];
    fgets(base_str, 3, stdin);
    int base;
    sscanf(base_str, "%d", &base);
    Array x;
    int err = create_arr(5, &x);
    if (err) {
        destroy(&x);
        return err;
    }
    int res = parse_str(&x);
    long long max = LLONG_MIN;
    while (res == 0) {
        long long dec;
        err = to_decimal(x, base, &dec);
        if (err)
            return err;
        if (dec > max)
            max = dec;
        res = parse_str(&x);
    }
    if (res > 0) {
        return res;
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
