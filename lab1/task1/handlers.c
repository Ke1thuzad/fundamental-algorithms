#include <math.h>
#include <malloc.h>
#include <string.h>
#include "main.h"

void natural_numbers(unsigned int x) {
    unsigned char key = 0;
    for (int i = 1; i < 101; ++i) {
        if (i % x == 0) {
            key = 1;
            printf_s("%d ", i);
        }
    }
    if (!key) printf_s("None");
    printf_s("\n");
}

void is_prime(unsigned int x) {
    for (int i = 2; i < (int)sqrt((double)x) + 1; ++i) {
        if (x % i == 0) {
            printf_s("%d is a compound number.", x);
            return;
        }
    }
    printf_s("%d is a prime number", x);
}

void to_base16(unsigned int x) {
    int size = (int)(log2(x) * 0.25) + 1, i = size - 1;
    char result[size];
    char letters[16] = "0123456789ABCDEF";

    while (x > 0) {
        result[i--] = letters[x % 16];
        x /= 16;
    }

    for (int j = 0; j < size; ++j) {
        if (result[j])
            printf_s("%c ", result[j]);
    }
    printf_s("\n");

}

void exponent_table(unsigned int x) {
    if (x > 10 || x < 1) exit(OUT_OF_BOUNDS);

    for (int i = 1; i < 11; ++i) {
        for (int j = 1; j <= x; ++j) {
            printf_s("%llu ", power(j, i));
        }
        printf_s("\n");
    }
}

long long power(unsigned int x, unsigned int y) {
    long long result = x;
    for (int i = 1; i < y; ++i) {
        result *= x;
    }
    return result;
}

void natural_sum(unsigned int x) {
    if (x < 1) exit(OUT_OF_BOUNDS);
    printf_s("%d", x * (1 + x) / 2);
}

void factorial(unsigned int x) {
    if (x == 0) printf_s("1");

    Array result = value_to_arr(x);
    for (int i = 1; i < x; ++i) {
        result = multiply(result, i);
    }
    reverse_print_arr(result);
}

Array create_arr(unsigned int length) {
    Array arr;
    arr.capacity = length;
    arr.length = 0;
    arr.val = malloc(length);

    return arr;
}

int append(Array* arr, unsigned char value) {
    if (arr->length >= arr->capacity) extend(arr);

    arr->val[arr->length++] = value;
    return 1;
}

void resize(Array* arr, int size_delta) {
    unsigned char* new_addr = malloc(arr->capacity + size_delta);
    if (!new_addr) return;
    memmove(new_addr, arr->val, arr->length);
    arr->val = new_addr;
    arr->capacity += size_delta;
}

// Double array length.
void extend(Array* arr) {
    resize(arr, arr->capacity);
}

void print_arr(const Array arr) {
    for (int i = 0; i < arr.length; ++i) {
        printf_s("%u ", arr.val[i]);
    }
}

void reverse_print_arr(const Array arr) {
    for (int i = arr.length - 1; i >= 0; --i) {
        printf_s("%u", arr.val[i]);
    }
}

Array value_to_arr(unsigned int value) {
    Array result = create_arr((int)log10((double)value) + 1);
    while (value > 0) {
        append(&result, value % 10);
        value /= 10;
    }
    return result;
}

Array multiply(const Array A, unsigned int B) {
    Array result = create_arr(A.capacity + 5);
    int shift = 0;

    for (int i = 0; i < A.length; i++) {
        int product = A.val[i] * B + shift;
        shift = product / 10;
        append(&result, product % 10);
    }

    while (shift > 0) {
        append(&result, shift % 10);
        shift /= 10;
    }

    return result;
}