#include "main.h"

int main(int argc, char** argv) {
    if (argc != 3)
        return throw_err(INCORRECT_ARGUMENTS);

    int a, b, err = parse_int(argv[1], &a) | parse_int(argv[2], &b);
    if (err)
        return err;
    if (a == 0 && b == 0)
        return throw_err(INCORRECT_ARGUMENTS);

    err = part_one(a, b);
    if (err)
        return err;

    err = part_two();
    return err;
}