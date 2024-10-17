#include "main.h"

int base_sum(int base, Array* result, int count, ...) {
    if (base < 2 || base > 36)
        return throw_err(INCORRECT_ARGUMENTS);

    if (count < 0)
        return throw_err(INCORRECT_ARGUMENTS);

    va_list vals;
    Array temp, temp2;
    int err = create_arr(2, &temp);
    if (err)
        return err;

    err = create_arr(2, &temp2);
    if (err)
        return err;

    err = append(&temp, '0');
    if (err)
        return err;

    va_start(vals, count);
    for (int i = count; i--;) {
        str_to_arr(va_arg(vals, char*), &temp2);
        err = add_arrays_base(temp, temp2, result, base);
        if (err)
            return err;
        copy(&temp, result);
    }
    destroy(&temp);
    destroy(&temp2);
    va_end(vals);

    return 0;
}

int main() {
    Array result;
    int err = create_arr(5, &result);
    if (err)
        return err;
                                // 2 + 21 + 15 = 38 = 1102
    err = base_sum(3, &result, 4, "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001", "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000210", "120", "001");
    if (err) {
        destroy(&result);
        return err;
    }
    print_arr(result);

    err = base_sum(36, &result, 4, "z", "000000000000000000000z", "0", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    if (err) {
        destroy(&result);
        return err;
    }
    print_arr(result);

    destroy(&result);

    return 0;
}
