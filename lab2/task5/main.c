#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "main.h"

// Прототипы функций
int overfprintf(FILE* stream, const char* format, ...);
int oversprintf(char* buf, const char* format, ...);

// Тесты для overfprintf
void test_overfprintf() {
    FILE *file = fopen("test_output.txt", "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    // Тест на флаг "Ro" (Римские цифры)
    overfprintf(file, "Roman numeral of 1984: %Ro\n", 1984);

    // Тест на флаг "Zr" (Числа Фибоначчи)
    overfprintf(file, "Zeckendorf representation of 20: %Zr\n", 20);

    // Тест на флаг "Cv" (Конвертация в другую систему счисления)
    overfprintf(file, "Base 16 representation of 255: %Cv\n", 255, 16);

    // Тест на флаг "CV" (Конвертация в другую систему счисления с верхним регистром)
    overfprintf(file, "Base 16 representation of 255 (uppercase): %CV\n", 255, 16);

    // Тест на флаг "to" (Конвертация из другой системы счисления в десятичную)
    overfprintf(file, "Decimal representation of 'FF' in base 16: %to\n", "FF", 16);

    // Тест на флаг "mi" (Бинарное представление int)
    overfprintf(file, "Binary representation of -1: %mi\n", -1);

    // Тест на флаг "mu" (Бинарное представление unsigned int)
    overfprintf(file, "Binary representation of 4294967295: %mu\n", 4294967295);

    // Тест на флаг "md" (Бинарное представление double)
    overfprintf(file, "Binary representation of 3.14: %md\n", 3.14);

    // Тест на флаг "mf" (Бинарное представление float)
    overfprintf(file, "Binary representation of 3.14f: %mf\n", 3.14f);

    fclose(file);

    // Проверка результатов
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

// Тесты для oversprintf
void test_oversprintf() {
    char buffer[1024] = {};

    // Тест на флаг "Ro" (Римские цифры)
    oversprintf(buffer, "Roman numeral of 1984: %Ro\n", 1984);
    printf("%s", buffer);
    assert(strcmp(buffer, "Roman numeral of 1984: MCMLXXXIV\n") == 0);

    // Тест на флаг "Zr" (Числа Фибоначчи)
    oversprintf(buffer, "Zeckendorf representation of 20: %Zr\n", 20);
    printf("%s", buffer);
    assert(strcmp(buffer, "Zeckendorf representation of 20: 2 5 13 1\n") == 0);

    // Тест на флаг "Cv" (Конвертация в другую систему счисления)
    oversprintf(buffer, "Base 16 representation of 255: %Cv\n", 255, 16);
    printf("%s", buffer);
    assert(strcmp(buffer, "Base 16 representation of 255: ff\n") == 0);

    // Тест на флаг "CV" (Конвертация в другую систему счисления с верхним регистром)
    oversprintf(buffer, "Base 16 representation of 255 (uppercase): %CV\n", 255, 16);
    printf("%s", buffer);
    assert(strcmp(buffer, "Base 16 representation of 255 (uppercase): FF\n") == 0);

    // Тест на флаг "to" (Конвертация из другой системы счисления в десятичную)
    oversprintf(buffer, "Decimal representation of 'FF' in base 16: %to\n", "FF", 16);
    printf("%s", buffer);
    assert(strcmp(buffer, "Decimal representation of 'FF' in base 16: 255\n") == 0);

    // Тест на флаг "mi" (Бинарное представление int)
    oversprintf(buffer, "Binary representation of -1: %mi\n", -1);
    printf("%s", buffer);
    assert(strcmp(buffer, "Binary representation of -1: 11111111 11111111 11111111 11111111\n") == 0);

    // Тест на флаг "mu" (Бинарное представление unsigned int)
    oversprintf(buffer, "Binary representation of 4294967295: %mu\n", 4294967295);
    printf("%s", buffer);
    assert(strcmp(buffer, "Binary representation of 4294967295: 11111111 11111111 11111111 11111111\n") == 0);

    // Тест на флаг "md" (Бинарное представление double)
    oversprintf(buffer, "Binary representation of 3.14: %md\n", 3.14);
    printf("%s", buffer);
//    assert(strcmp(buffer, "Binary representation of 3.14: 01000000 00001001 00001111 01011100 00101000 11110101 11000010 10001111\n") == 0);

    // Тест на флаг "mf" (Бинарное представление float)
    oversprintf(buffer, "Binary representation of 3.14f: %mf\n", 3.14f);
    printf("%s", buffer);
//    assert(strcmp(buffer, "Binary representation of 3.14f: 01000000 01001000 11110101 11000011\n") == 0);
}

int main() {
    test_overfprintf();
    test_oversprintf();
    return 0;
}