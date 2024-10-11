#include "main.h"

int GetOpts(int argc, char** argv, kOpts *option, Array* paths) {
    if (argc < 4 || argc > 5) {
        return throw_err(INCORRECT_ARGUMENTS);
    }

    const char* proceeding_option = argv[1];
    if ((proceeding_option[0] == '/' || proceeding_option[0] == '-')) {
        if (proceeding_option[2])
            return throw_err(INCORRECT_OPTION);

        int i = 0;
        for (; i < 2; ++i) {
            int err = str_to_arr(argv[i + 2], &paths[i]);
            if (err)
                return err;
        }
        switch (proceeding_option[1])
        {
            case 'r':
                if (argc != 5)
                    return throw_err(INCORRECT_ARGUMENTS);
                *option = OPT_R;
                int err = str_to_arr(argv[i + 2], &paths[i]);
                if (err)
                    return err;
                break;
            case 'a':
                if (argc != 4)
                    return throw_err(INCORRECT_ARGUMENTS);
                *option = OPT_A;
                break;
            default:
                return throw_err(INCORRECT_OPTION);
        }
    } else {
        return throw_err(INCORRECT_ARGUMENTS);
    }

    if (!is_unique(paths, 3))
        return throw_err(INCORRECT_ARGUMENTS);

    return 0;
}

int main(int argc, char** argv) {
    kOpts opt;
    handler handlers[2] = {
            handler_r,
            handler_a
    };
    Array* paths = (Array*) malloc(sizeof(Array) * 3);

    for (int i = 0; i < 3; ++i) {
        create_arr(1, &paths[i]);
    }

    int err = GetOpts(argc, argv, &opt, paths);
    if (err) {
        for (int i = 0; i < 3; ++i) {
            destroy(&paths[i]);
        }
        free(paths);
        return err;
    }

    err = handlers[opt](paths);

    for (int i = 0; i < 3; ++i) {
        destroy(&paths[i]);
    }
    free(paths);
    if (err) {
        return err;
    }

    return 0;
}
