#include "main.h"

int main(int argc, char **argv) {
    if (argc != 2)
        return throw_err(INCORRECT_ARGUMENTS);

    FILE *in = fopen(argv[1], "r");

    return dialog_manager(in);
}

