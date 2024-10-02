#include "main.h"

int GetOpts(int argc, char** argv, kOpts *option, int *number, int* minus_sign) {
    if (argc != 3) {
        return throw_err(INCORRECT_ARGUMENTS);
    }

    for (int i = 1; i <= 2; ++i)
    {
        const char* proceeding_option = argv[i];
        if ((proceeding_option[0] == '/' || proceeding_option[0] == '-') && !proceeding_option[2])
        {
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
                    return throw_err(INCORRECT_OPTION);
            }
        } else {
            int lst;
            *minus_sign = 0;
            if (proceeding_option[0] == '-')
                *minus_sign = 1;
            for (int j = *minus_sign; proceeding_option[j]; ++j) {
                lst = *number;
                if (proceeding_option[j] >= '0' && proceeding_option[j] <= '9') {
                    *number *= 10;
                    *number += proceeding_option[j] - '0';
                    if (*number <= lst || *number % 10 != proceeding_option[j] - '0') {
                        return throw_err(INCORRECT_ARGUMENTS);
                    }
                } else {
                    return throw_err(INCORRECT_ARGUMENTS);
                }
            }
        }
    }
    return 0;
}

int main (int argc, char** argv) {
    kOpts opt = 0;
    int proceed_number = 0, minus_sign;
    int (*handlers[5])(unsigned int) = {
            natural_numbers,
            is_prime,
            exponent_table,
            natural_sum,
            factorial
    };
    int err = GetOpts(argc, argv, &opt, &proceed_number, &minus_sign);
    if (err) {
        return err;
    }
    if (opt == OPT_S) {
        return to_base16(proceed_number, minus_sign);
    }
    if (minus_sign)
        return throw_err(OUT_OF_BOUNDS);
    return handlers[opt](proceed_number);
}
