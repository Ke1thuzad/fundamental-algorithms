#include "main.h"

int main(int argc, char **argv) {
    if (argc != 3)
        return throw_err(INCORRECT_ARGUMENTS);

    char *in = argv[1];
    char *out = argv[2];

    if (check_paths(in, out))
        return throw_err(INCORRECT_ARGUMENTS);

    StudentArr studentArr;
    create_studarr(5, &studentArr);

    FILE* inp = fopen(in, "r");

    int err = read_students(inp, &studentArr);

    StudentArr res;
    create_studarr(5, &res);
    SearchParameter searchType;
//    searchType.str = str;
    str_to_arr("danil", &searchType.str);

    student_search(studentArr, NAME, searchType, &res);
    for (int i = 0; i < res.length; ++i) {
        printf("%d\n", res.val[i].id);
    }
//    if (err)
//        return err;
    destroy_stud(&studentArr);
    destroy_stud(&res);

    return err;
}