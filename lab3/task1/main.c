#include "main.h"

int adder(int a, int b) {
    int carry = 0;

    while (b != 0) {
        carry = a & b;

        a ^= b;
        b = carry << 1;
    }

    return a;
}

int to_base_r(int a, int base, char* result, int length) {
    if (base < 1 || base > 5)
        return throw_err(INCORRECT_ARGUMENTS);

    int negative = 0;
    int mask = 0, i = 0;

    if (a < 0) {
        result[i] = '-';
        i = adder(i, 1);
        negative = 1;
        a = adder(~a, 1);
    }

    char letters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (a > 0 && i < length) {
        mask = a & (adder(1 << base, adder(~1, 1)));
        result[i] = letters[mask];
        i = adder(i, 1);

        a >>= base;
    }

    result[i] = '\0';
    i = adder(i, -1);

    for (int j = negative; j < adder(i, adder(1, negative)) >> 1; j = adder(j, 1)) {
        char swapped = result[j];
        int rind = adder(adder(i, adder(~j, 1)), negative);
        result[j] = result[rind];
        result[rind] = swapped;
    }

    return 0;
}

int main() {
    char a[100];
    to_base_r(1024, 1, a, 100);

    printf("%s", a);

    return 0;
}
