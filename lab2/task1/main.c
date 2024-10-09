#include "main.h"

int getOpts(int argc, char*** argv, kOpts *option) {

    if (argc < 3) return throw_err(INCORRECT_ARGUMENTS);

    const char *proceeding_option = (*argv)[1];
    if ((proceeding_option[0] == '/' || proceeding_option[0] == '-') && !proceeding_option[2]) {
        switch (proceeding_option[1]) {
            case 'l':
                if (argc != 3)
                    return throw_err(INCORRECT_ARGUMENTS);
                *option = OPT_L;
                break;
            case 'r':
                if (argc != 3)
                    return throw_err(INCORRECT_ARGUMENTS);
                *option = OPT_R;
                break;
            case 'u':
                if (argc != 3)
                    return throw_err(INCORRECT_ARGUMENTS);
                *option = OPT_U;
                break;
            case 'n':
                if (argc != 3)
                    return throw_err(INCORRECT_ARGUMENTS);
                *option = OPT_N;
                break;
            case 'c':
                *option = OPT_C;
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
    option handlers[5] = {
            handler_l,
            handler_r,
            handler_u,
            handler_n,
            handler_c
    };

    Array result;
    int err = create_arr(5, &result);
    if (err)
        return err;

    err = getOpts(argc, &argv, &opt);
    if (err) {
        destroy(&result);
        return err;
    }
    err = handlers[opt](argv, &result);
    if (err) {
        destroy(&result);
        return err;
    }
    print_arr(result);
    destroy(&result);

    return 0;
}
