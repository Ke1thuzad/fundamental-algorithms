//#include "main.h"
//
//int dialog_manager(FILE* in, FILE* out) {
//    DialogFSM state = COMMAND_WAIT;
//    Command cmd;
//
//    StudentArr students;
//    int err = create_studarr(5, &students);
//    if (err)
//        return err;
//
//    err = read_students(in, &students);
//
//    fclose(in);
//    if (err) {
//        destroy_stud(&students);
//        return err;
//    }
//
//    printf("Please input your command (or type 'help' for info).\n");
//
//    while (1) {
//        switch (state) {
//            case COMMAND_WAIT:
//                err = wait_command(&cmd);
//                if (err) {
//                    destroy_stud(&students);
//                    return 0;
//                }
//
//                state = COMMAND_HANDLE;
//                break;
//            case COMMAND_HANDLE:
//                err = handle_command(cmd, &students, out);
//                if (err == EOF) {
//                    destroy_stud(&students);
//                    return 0;
//                }
//
//                if (err) {
//                    destroy_stud(&students);
//                    return err;
//                }
//
//                state = COMMAND_WAIT;
//                break;
//            default:
//                destroy_stud(&students);
//                return throw_err(INCORRECT_OPTION);
//        }
//    }
//
////    destroy_stud(&students);
////    return 0;
//}
//
//int wait_command(Command *result) {
//    Array buf;
//    int err = create_arr(5, &buf);
//    if (err)
//        return err;
//
//    while (1) {
//        printf("> %s", "\0");
//        overfscanf(stdin, " %S", &buf);
//        printf("\n");
//
//        if (is_str_equal(buf.val, "^Z")) {
//            destroy(&buf);
//            return 1;
//        } else if (is_str_equal(buf.val, "help")) {
//            *result = HELP;
//            break;
//        } else if (is_str_equal(buf.val, "print")) {
//            *result = PRINT;
//            break;
//        } else if (is_str_equal(buf.val, "search")) {
//            *result = SEARCH;
//            break;
//        } else if (is_str_equal(buf.val, "sort")) {
//            *result = SORT;
//            break;
//        } else if (is_num(buf.val[0]) && buf.length == 1) {
//            *result = buf.val[0] - '0' - 1;
//
//            break;
//        } else {
//            printf("Incorrect command. Please try again or use 'help' command.\n");
//        }
//        reset(&buf);
//    }
//
//    destroy(&buf);
//
//    return 0;
//}
//
//int handle_command(Command cmd, StudentArr *students, FILE *out) {
//    int param = 0;
//    int err = 0;
//
//    switch (cmd) {
//        case HELP:
//            help_cmd();
//            break;
//        case PRINT:
//            err = wait_param(cmd, &param);
//            if (err == EOF)
//                return err;
//
//            if (err)
//                break;
//
//            if (param < 0 || param > 1) {
//                throw_err(INCORRECT_OPTION);
//                return 0;
//            }
//
//            err = print_cmd(out, *students, param);
//            if (err)
//                return err;
//
//            break;
//        case SEARCH:
//            err = wait_param(cmd, &param);
//            if (err == EOF)
//                return err;
//
//            if (err)
//                break;
//
//            if (param < ID || param > MEAN) {
//                throw_err(INCORRECT_OPTION);
//                return 0;
//            }
//
//            SearchParameter searchParameter;
//
//            if (param != MEAN) {
//                err = create_arr(5, &searchParameter.str);
//                if (err)
//                    return err;
//
//                err = wait_search_param(param, &searchParameter);
//                if (err) {
//                    if (param >= NAME && param <= GROUP)
//                        destroy(&searchParameter.str);
//                    return -1;
//                }
//            } else {
//                searchParameter.mean = all_student_mean(*students);
//            }
//
//            StudentArr found;
//            err = create_studarr(5, &found);
//            if (err) {
//                if (param >= NAME && param <= GROUP)
//                    destroy(&searchParameter.str);
//                return err;
//            }
//
//            err = search_cmd(*students, param, searchParameter, &found);
//
//
//            err = write_students(out, found, 1);
//
//            destroy_stud(&found);
//            if (param >= NAME && param <= GROUP)
//                destroy(&searchParameter.str);
//
//            if (err) {
//                return err;
//            }
//
//            break;
//        case SORT:
//            err = wait_param(cmd, &param);
//            if (err == EOF)
//                return err;
//
//            if (err)
//                break;
//
//            if (param < ID || param > GROUP) {
//                throw_err(INCORRECT_OPTION);
//                return 0;
//            }
//
//            err = sort_cmd(students, param);
//            if (err)
//                return err;
//            break;
//        default:
//            return throw_err(INCORRECT_OPTION);
//    }
//
//    return 0;
//}
//
//int wait_param(Command cmd, int *param) {
//    switch (cmd) {
//        case PRINT:
//            cmd_description(PRINT);
//            break;
//        case SEARCH:
//            cmd_description(SEARCH);
//            break;
//        case SORT:
//            cmd_description(SORT);
//            break;
//        default:
//            return throw_err(INCORRECT_OPTION);
//    }
//
//
//    printf("Please enter function parameter: \n");
//
//    int scan_read = scanf("%d", param);
//
//    if (scan_read == EOF) {
//        return EOF;
//    } else if (!scan_read) {
//        printf("Incorrect parameter. Please try again.\n");
//        return 1;
//    } else {
//        *param -= 1;
//        return 0;
//    }
//}
//
//int wait_search_param(SearchCriteria criteria, SearchParameter *searchParam) {
//    printf("Please enter parameter to search for: \n");
//    int scan_read = 0;
//    int err;
//
//    switch (criteria) {
//        case ID:
//            destroy(&searchParam->str);
//
//            scan_read = scanf("%u", &searchParam->id);
//            break;
//        case MEAN:
//            destroy(&searchParam->str);
//            scan_read = scanf("%f", &searchParam->mean);
//            break;
//        case NAME:
//        case SURNAME:
//        case GROUP:
//            scan_read = overfscanf(stdin, "%S", &searchParam->str);
//            break;
//        default:
//            destroy(&searchParam->str);
//            return throw_err(INCORRECT_OPTION);
//    }
//
//    if (scan_read == EOF) {
//        return 1;
//    } else if (!scan_read) {
//        throw_err(INCORRECT_ARGUMENTS);
//        return 0;
//    } else {
//        return 0;
//    }
//}
//
//void cmd_description(Command cmd) {
//    int level = 1;
//    int j = 1;
//
//    char* cmd_descriptions[4][10] = {
//            {"'help' - Print all available commands and their options"},
//            {"'print' - Print information about students", "All grades", "Mean grade only", NULL},
//            {"'search' - Search students by parameters", "ID", "Name", "Surname", "Group", "Mean", NULL},
//            {"'sort' - Sort students by parameters", "ID", "Name", "Surname", "Group", NULL},
//    };
//
//    printf("%*d. %s.\n", level * 2, cmd + 1, cmd_descriptions[cmd][0]);
//    level++;
//    while (cmd_descriptions[cmd][j] != NULL) {
//        printf("%*d) %s.\n", level * 2, j, cmd_descriptions[cmd][j]);
//
//        j++;
//    }
//
//}
//
//void help_cmd() {
//    int cmd_amount = 4;
//
//    printf("Available commands (you can use them by typing numbers corresponding or command strings):\n");
//    for (int i = 1; i <= cmd_amount; ++i) {
//        cmd_description(i - 1);
//    }
//}
//
//int print_cmd(FILE* out, StudentArr students, int param) {
//    if (param < 0 || param > 1) {
//        return throw_err(INCORRECT_OPTION);
//    }
//
//    write_students(out, students, param);
//
//    return 0;
//}
//
//int search_cmd(StudentArr students, SearchCriteria criteria, SearchParameter searchParam, StudentArr *found_students) {
//    int read = student_search(students, criteria, searchParam, found_students);
//
//    printf("\nFound %d occurrences:\n", read);
//
//    return 0;
//}
//
//int sort_cmd(StudentArr *students, int param) {
//    switch (param) {
//        case 0:
//            qsort(students->val, students->length, sizeof(Student), cmp_student_id);
//            break;
//        case 1:
//            qsort(students->val, students->length, sizeof(Student), cmp_student_name);
//            break;
//        case 2:
//            qsort(students->val, students->length, sizeof(Student), cmp_student_surname);
//            break;
//        case 3:
//            qsort(students->val, students->length, sizeof(Student), cmp_student_group);
//            break;
//        default:
//            return throw_err(INCORRECT_OPTION);
//    }
//
//    return 0;
//}
