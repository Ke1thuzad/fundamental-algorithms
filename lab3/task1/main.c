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

    char letters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int mask = 0, i = 0;

    while (a > 0 && i < length) {
        mask = a & (adder(1 << base, -1));
        result[i] = letters[mask];
        i = adder(i, 1);

        a >>= base;
    }

    result[i] = '\0';

    for (int j = 0; j < i >> 1; j = adder(j, 1)) {
        char swapped = result[j];
        int rind = adder(adder(i, -j), -1);
        result[j] = result[rind];
        result[rind] = swapped;
    }

    return 0;
}

int main() {
    char a[100];
    to_base_r(2353529, 3, a, 100);

    printf("%s", a);

    return 0;
}
