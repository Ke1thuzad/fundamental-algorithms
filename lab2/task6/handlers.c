#include "main.h"

int roman_value(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

int unroman(char *str, int *result) {
    int total = 0;
    int i = 0;
    int prev = 0;

    while (str[i] != '\0') {
        int current_value = roman_value(str[i]);

        total += current_value;

        if (current_value > prev) {
            total -= prev * 2;
        }

        prev = current_value;
        i++;
    }

    *result = total;

    return 0;
}

int unzeckendorf() {
    unsigned int result = 0;


}
