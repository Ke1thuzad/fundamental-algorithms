#include "main.h"

void getOpts(int argc, char*** argv, kOpts *option) {

    if (argc < 2 || argc > 6) exit(INCORRECT_ARGUMENTS);

    const char *proceeding_option = (*argv)[1];
    if ((proceeding_option[0] == '/' || proceeding_option[0] == '-') && !proceeding_option[2]) {
        switch (proceeding_option[1]) {
            case 'q':
                if (argc != 6) exit(INCORRECT_ARGUMENTS);
                *option = OPT_Q;
                break;
            case 'm':
                if (argc != 4) exit(INCORRECT_ARGUMENTS);
                *option = OPT_M;
                break;
            case 't':
                if (argc != 6) exit(INCORRECT_ARGUMENTS);
                *option = OPT_T;
                break;
            default:
                exit(INCORRECT_OPTION);
        }
    } else {
        exit(INCORRECT_ARGUMENTS);
    }

    *argv += 2;

}

int main(int argc, char** argv) {
    kOpts opt;
    option handlers[3] = {
            option_q,
            option_m,
            option_t
    };

    getOpts(argc, &argv, &opt);
    handlers[opt](argv);

    return 0;
}

