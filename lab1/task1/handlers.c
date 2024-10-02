#include "main.h"

int natural_numbers(unsigned int x) {
    unsigned char key = 0;
    for (int i = x; i < 101; i += x) {
        printf("%d ", i);
    }
    printf("\n");
    return 0;
}

int is_prime(unsigned int x) {
    if (x == 1) {
        printf("%d is neither a compound, nor a prime number.", x);
        return 0;
    }
    for (int i = 2; i <= (int)sqrt((double)x); ++i) {
        if (x % i == 0) {
            printf("%d is a compound number.\n", x);
            return 0;
        }
    }
    printf("%d is a prime number.\n", x);
    return 0;
}

int to_base16(unsigned int x, int minus_sign) {
    char result[512];
    int size = sizeof(result), i = 0;
    to_base(x, 16, result, size);

    if (minus_sign)
        printf("- ");

    while (result[i] != '\0') {
        printf("%c ", result[i++]);
    }
    printf("\n");
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

int exponent_table(unsigned int x) {
    if (x > 10 || x < 1) 
        return throw_err(OUT_OF_BOUNDS);

    for (int i = 1; i < 11; ++i) {
        for (int j = 1; j <= x; ++j) {
            printf("%llu ", power(j, i));
        }
        printf("\n");
    }
    return 0;
}

long long power(unsigned int x, unsigned int y) {
    long long result = x;
    for (int i = 1; i < y; ++i) {
        result *= x;
    }
    return result;
}

int natural_sum(unsigned int x) {
    if (x < 1) 
        return throw_err(OUT_OF_BOUNDS);
    printf("%d", x * (1 + x) / 2);
    return 0;
}

int factorial(unsigned int x) {
    if (x > 20) {
        return throw_err(OUT_OF_BOUNDS);
    }

    long long int result = 1;
    if (x == 0) {
        printf("Factorial of %d: %lld", x, result);
        return 0;
    }
    for (int i = 1; i <= x; ++i) {
        result *= i;
    }
    printf("Factorial of %d: %lld", x, result);
    return 0;
}