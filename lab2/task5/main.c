#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "main.h"

void test_overfprintf() {
    FILE *file = fopen("test_output.txt", "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    overfprintf(file, "Roman numeral of 1984: %Ro\n", 1984);

    overfprintf(file, "Zeckendorf representation of 20: %Zr\n", 20);

    overfprintf(file, "Base 16 representation of 255: %Cv\n", 255, 16);

    overfprintf(file, "Base 16 representation of 255 (uppercase): %CV\n", 255, 16);

    overfprintf(file, "Decimal representation of 'FF' in base 16: %to\n", "FF", 16);
//    overfprintf(file, "Decimal representation of 'FF' in base 16: %to\n", "FF", 16);
    overfprintf(file, "Decimal representation of 'FF' in base 16: %TO\n", "FF", 16);

    overfprintf(file, "Binary representation of -1: %mi\n", -1);

    overfprintf(file, "Binary representation of 4294967295: %mu\n", 4294967295);

    overfprintf(file, "Binary representation of 3.14: %md\n", 3.14);

    overfprintf(file, "Binary representation of 3.14f: %mf\n", 3.14f);

    fclose(file);

    FILE *check_file = fopen("test_output.txt", "r");
    if (!check_file) {
        perror("Failed to open file for checking");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), check_file)) {
        printf("%s", buffer);
    }

    fclose(check_file);
}

void test_oversprintf() {
    char buffer[1024] = {};

    oversprintf(buffer, "Roman numeral of 1984: %Ro\n", 1984);
    printf("%s", buffer);
    assert(strcmp(buffer, "Roman numeral of 1984: MCMLXXXIV\n") == 0);

    oversprintf(buffer, "Zeckendorf representation of 20: %Zr\n", 2023456765433456787);
    printf("%s", buffer);

    oversprintf(buffer, "Base 16 representation of 255: %Cv\n", 255, 16);
    printf("%s", buffer);
    assert(strcmp(buffer, "Base 16 representation of 255: ff\n") == 0);

    oversprintf(buffer, "Base 16 representation of 255 (uppercase): %CV\n", 255, 16);
    printf("%s", buffer);
    assert(strcmp(buffer, "Base 16 representation of 255 (uppercase): FF\n") == 0);

    oversprintf(buffer, "Decimal representation of 'FF' in base 16: %to\n", "FF", 16);
    printf("%s", buffer);
//    assert(strcmp(buffer, "Decimal representation of 'FF' in base 16: 255\n") == 0);

    oversprintf(buffer, "Binary representation of -1: %mi\n", -1);
    printf("%s", buffer);
    assert(strcmp(buffer, "Binary representation of -1: 11111111 11111111 11111111 11111111\n") == 0);

    oversprintf(buffer, "Binary representation of 4294967295: %mu\n", 4294967295);
    printf("%s", buffer);
    assert(strcmp(buffer, "Binary representation of 4294967295: 11111111 11111111 11111111 11111111\n") == 0);

    oversprintf(buffer, "Binary representation of 3.14: %md\n", 3.14);
    printf("%s", buffer);

    oversprintf(buffer, "Binary representation of 3.14f: %mf\n", 3.14f);
    printf("%s", buffer);
}

int main() {
//    test_overfprintf();
//    test_oversprintf();
    int a = -57;
    printf("%%\n");
    overfprintf(stdout, "%%%d%Ro%1d%lld%Ro%mi%*d", 1, 1, 1, 1, 1, 1, 1);
//    int err = overfprintf(stdout, "%Zr%Ro%Zr %d\n\t%TO", 51, 3999, 50, 5123, "ASD", 36);
//    if (err)
//        return err;

    return 0;
}