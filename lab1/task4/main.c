#include "main.h"

int GetOpts(int argc, char** argv, kOpts *option, char* in_path, char* out_path) {
    if (argc < 2 || argc > 4) {
        return 1;
    }

    unsigned char arg_index = 1, flag = 0;

    for (int i = 1; i <= 2; ++i) {
        const char* proceeding_option = argv[i];
        if ((proceeding_option[0] == '/' || proceeding_option[0] == '-')) {
            if (proceeding_option[1] == 'n') {
                string_copy(out_path, argv[3]);
                arg_index = 2;
            } else if (proceeding_option[2]) {
                throw_err(INCORRECT_ARGUMENTS);
            } else {
                flag = 1;
            }

            switch (proceeding_option[arg_index])
            {
                case 'd':
                    *option = OPT_D;
                    break;
                case 'i':
                    *option = OPT_I;
                    break;
                case 's':
                    *option = OPT_S;
                    break;
                case 'a':
                    *option = OPT_A;
                    break;
                default:
                    throw_err(INCORRECT_OPTION);
            }
        } else {
            string_copy(in_path, proceeding_option);
        }

    }
    if (flag) {
        strcpy(out_path + 4, in_path);
    }

    return 0;
}

int main (int argc, char** argv) {
    kOpts opt = 0;
    char out_path[512] = "out_", in_path[512];
    handler handlers[4] = {
        handler_option_d,
        handler_option_i,
        handler_option_s,
        handler_option_a
    };

    if (GetOpts(argc, argv, &opt, in_path, out_path)) {
        printf("%s", "Incorrect option");
        throw_err(INCORRECT_OPTION);
    }
    process_files(in_path, out_path, handlers[opt]);
    return 0;
}
