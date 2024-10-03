#include "main.h"

int main(int argc, char** argv) {
    if (argc != 3)
        return throw_err(INCORRECT_ARGUMENTS);

    Array* paths = malloc(sizeof(Array) * 2);
    int err;
    if (!paths)
        return throw_err(MEMORY_NOT_ALLOCATED);
    for (int i = 1; i < 3; ++i) {
        create_arr(2, &paths[i - 1]);
        err = str_to_arr(argv[i], &paths[i - 1]);
    }
    handler(paths);

    for (int i = 0; i < 2; ++i) {
        destroy(&paths[i]);
    }
    free(paths);
    if (err)
        return err;

//    Array* arr = malloc(sizeof(Array));
//    Array* arr2 = malloc(sizeof(Array));
//    create_arr(5, arr);
//    append(arr, '6');
////    append(&arr, '9');
//    Array *res = malloc(sizeof(Array));
//    multiply(*arr, 25, res);
//    copy(arr, res);
//    print_arr(*res);
//    print_arr(*arr);
//    multiply(*arr, 12, res);
//    print_arr(*res);
//    print_arr(*arr);
//    add_arrays(*arr, *res, arr2);
//    print_arr(*arr2);
    return 0;
}
