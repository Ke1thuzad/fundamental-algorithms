#include "main.h"

int main(int argc, char** argv) {
    if (argc != 3)
        return throw_err(INCORRECT_ARGUMENTS);

    Array* paths = malloc(sizeof(Array) * 2);
    int err;
    if (!paths)
        return throw_err(MEMORY_NOT_ALLOCATED);
    for (int i = 1; i < 3; ++i) {
        err = create_arr(2, &paths[i - 1]);
        if (err) {
            for (int j = 0; j < 2; ++j) {
                destroy(&paths[j]);
            }
            free(paths);
            return err;
        }
        err = str_to_arr(argv[i], &paths[i - 1]);
        if (err) {
            for (int j = 0; j < 2; ++j) {
                destroy(&paths[j]);
            }
            free(paths);
            return err;
        }
    }

    if (!is_unique(paths, 2)) {
        for (int i = 0; i < 2; ++i) {
            destroy(&paths[i]);
        }
        free(paths);
        return throw_err(INCORRECT_ARGUMENTS);
    }

    err = handler(paths);

    for (int i = 0; i < 2; ++i) {
        destroy(&paths[i]);
    }
    free(paths);
    if (err)
        return err;

    return 0;
}
