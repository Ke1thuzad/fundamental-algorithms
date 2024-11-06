#include "main.h"

int main(int argc, char **argv) {
    if (argc != 3)
        return throw_err(INCORRECT_ARGUMENTS);

    if (check_paths(argv[1], argv[2])) {
        return throw_err(INCORRECT_ARGUMENTS);
    }

    FILE *in = fopen(argv[1], "r");

    if (!in)
        return throw_err(FILE_ERROR);

    FILE *out = fopen(argv[2], "w");

    if (!out) {
        fclose(in);
        return throw_err(FILE_ERROR);
    }

    parse_expression(in, out);


    fclose(in);
    fclose(out);

    return 0;
}

int check_paths(char *in, char *out) {
    char inbuf[1000], outbuf[1000];

    realpath(in, inbuf);
    realpath(out, outbuf);

    if (is_str_equal(inbuf, outbuf)) {
        return 1;
    }

    return 0;
}
//
//int create_result_arr(unsigned int length, ResultArr *arr) {
//
//    arr->capacity = length;
//    arr->length = 0;
//    arr->val = (Result *) malloc(length * sizeof(Result));
////    for (int i = 0; i < length; ++i) {
////        arr->val[i] = malloc(sizeof(Array));
//////        int err = create_arr(5, arr->val);
//////        if (err)
//////            return err;
////    }
//
//    if (!arr->val)
//        return throw_err(MEMORY_NOT_ALLOCATED);
//
//    return 0;
//}
//
//int append_result(ResultArr *arr, Result *value) {
//    if (arr->length >= (arr->capacity - 1)) {
//        int err = extend_result(arr);
//        if (err)
//            return err;
//    }
//
//    arr->val[arr->length++].val = (Array*) malloc(sizeof(Array));
//    Result *cur = &arr->val[arr->length++];
//    if (!cur->val)
//        return throw_err(MEMORY_NOT_ALLOCATED);
//
//    int err = create_arr(5, cur->val);
//    if (err)
//        return err;
//
//    cur->level = value->level;
//    err = copy(cur->val, value->val);
//    if (err) {
//        return err;
//    }
//
//    return 0;
//}
//
//int resize_results(ResultArr *arr, int size_delta) {
//    Result *new_addr = (Result *) realloc(arr->val, arr->capacity + size_delta * sizeof(Result));
//
//    if (!new_addr) {
//        free(arr->val);
//        return throw_err(MEMORY_NOT_ALLOCATED);
//    }
//
//    arr->val = new_addr;
//    arr->capacity += size_delta;
//    return 0;
//}
//
//int extend_result(ResultArr *arr) {
//    return resize_results(arr, arr->capacity);
//}
//
//void destroy_results(ResultArr *arr) {
//    if (arr->val) {
//        for (int i = 0; i < arr->length; ++i) {
//            destroy(arr->val[i].val);
//            free(arr->val[i].val);
//        }
//
//        free(arr->val);
//    }
//
//    arr->val = NULL;
//    arr->length = 0;
//    arr->capacity = 0;
//}


int parse_expression(FILE *in, FILE *out) {
    int level = 0;

    while (1) {
        Array temp = {};
        int next_level = level;

        int err = create_arr(5, &temp);
        if (err)
            return err;

        err = overfscanf(in, "%S", &temp);
        if (err < 1)
            return err;

        for (int i = 0; i < temp.length; ++i) {
            if (temp.val[i] == '(') {
                next_level++;
                level++;
            }
            else if (temp.val[i] == ')') {
                if (next_level > 0)
                    next_level--;
            }
        }

        for (int j = 0; j < level; ++j) {
            fprintf(out, "    ");
        }

        for (int i = 0; i < temp.length; ++i) {
            if (temp.val[i] != ',' && temp.val[i] != '(' && temp.val[i] != ')')
                fprintf(out, "%c", temp.val[i]);
        }

        fprintf(out, "\n");
        level = next_level;
//        else if (temp.val[temp.length - 1] == ',') {
//            if (level > 0)
//                level--;
//        }

//        Result a = {level, &temp};
//        append_result(results, &a);
        if (fscanf(in, "\n")) {
            fprintf(out, "\n");
            level = 0;
        }
        destroy(&temp);
    }

}





















