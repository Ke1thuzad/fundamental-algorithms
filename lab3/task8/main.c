#include "main.h"

int main(int argc, char **argv) {
    if (argc != 2)
        return throw_err(INCORRECT_OPTION);

    FILE *in = fopen(argv[1], "r");
    if (!in)
        return throw_err(FILE_ERROR);

    int err = calculator(in);

    return err;
}

