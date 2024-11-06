#include "main.h"

int main(int argc, char **argv) {
    if (argc != 3)
        return throw_err(INCORRECT_ARGUMENTS);

    char *in = argv[1];
    char *out = argv[2];

    if (check_paths(in, out))
        return throw_err(INCORRECT_ARGUMENTS);

    FILE* inp = fopen(in, "r");
    if (!inp)
        return throw_err(FILE_ERROR);

    FILE* outfile = fopen(out, "w");
    if (!outfile) {
        fclose(inp);
        return throw_err(FILE_ERROR);
    }

    int err = dialog_manager(inp, outfile);

    fclose(outfile);

    return err;
}