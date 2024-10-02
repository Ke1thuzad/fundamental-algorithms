#include "main.h"

int getOpts(int argc, char*** argv, kOpts *option) {

    if (argc < 2 || argc > 6) return throw_err(INCORRECT_ARGUMENTS);

    const char *proceeding_option = (*argv)[1];
    if ((proceeding_option[0] == '/' || proceeding_option[0] == '-') && !proceeding_option[2]) {
        switch (proceeding_option[1]) {
            case 'q':
                if (argc != 6) return throw_err(INCORRECT_ARGUMENTS);
                *option = OPT_Q;
                break;
            case 'm':
                if (argc != 4) return throw_err(INCORRECT_ARGUMENTS);
                *option = OPT_M;
                break;
            case 't':
                if (argc != 6) return throw_err(INCORRECT_ARGUMENTS);
                *option = OPT_T;
                break;
            default:
                return throw_err(INCORRECT_OPTION);
        }
    } else {
        return throw_err(INCORRECT_ARGUMENTS);
    }

    *argv += 2;
    return 0;
}

int main(int argc, char** argv) {
    kOpts opt;
    option handlers[3] = {
            option_q,
            option_m,
            option_t
    };
    int err = getOpts(argc, &argv, &opt);
    if (err)
        return err;
    err = handlers[opt](argv);
    if (err)
        return err;

    return 0;
}

