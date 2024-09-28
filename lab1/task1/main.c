#include "main.h"

int GetOpts(int argc, char** argv, kOpts *option, int *number) {
    if (argc != 3) {
        return 1;
    }

    for (int i = 1; i <= 2; ++i) {
        const char* proceeding_option = argv[i];
        if ((proceeding_option[0] == '/' || proceeding_option[0] == '-') && !proceeding_option[2]) {
            switch (proceeding_option[1])
            {
                case 'h':
                    *option = OPT_H;
                    break;
                case 'p':
                    *option = OPT_P;
                    break;
                case 's':
                    *option = OPT_S;
                    break;
                case 'e':
                    *option = OPT_E;
                    break;
                case 'a':
                    *option = OPT_A;
                    break;
                case 'f':
                    *option = OPT_F;
                    break;
                default:
                    exit(INCORRECT_OPTION);
            }
        } else {
            int lst;
            for (int j = 0; proceeding_option[j]; ++j) {
                lst = *number;
                if (proceeding_option[j] >= '0' && proceeding_option[j] <= '9') {
                    *number *= 10;
                    *number += proceeding_option[j] - '0';
                    if (*number <= lst || *number % 10 != proceeding_option[j] - '0') {
                        printf("Possible int overflow.\n");
                    }
                } else {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main (int argc, char** argv) {
    kOpts opt = 0;
    int proceed_number = 0;
    void (*handlers[6])(unsigned int) = {
            natural_numbers,
            is_prime,
            to_base16,
            exponent_table,
            natural_sum,
            factorial
    };

    if (GetOpts(argc, argv, &opt, &proceed_number)) {
        printf("%s", "Incorrect option");
        exit(INCORRECT_OPTION);
    }

    handlers[opt](proceed_number);
    return 0;
}
