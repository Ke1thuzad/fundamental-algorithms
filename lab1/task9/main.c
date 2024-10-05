#include "main.h"

int main(int argc, char** argv) {
    if (argc != 3)
        return throw_err(INCORRECT_ARGUMENTS);

    int a, b, err = parse_int(argv[1], &a) | parse_int(argv[2], &b);
    if (err)
        return err;
//    part_one(a, b);
    part_two();
    return 0;
}