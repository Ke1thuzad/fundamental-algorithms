#include "main.h"

int dialog_manager(FILE *in) {
    DialogFSM state = COMMAND_WAIT;
    Command cmd;

    LiverList *livers = {};
    UndoStack undoStack;

    int err;

    err = create_stack(&undoStack);
    if (err)
        return err;

    Array filename;
    err = create_arr(5, &filename);
    if (err) {
        destroy_stack(&undoStack);
        return err;
    }

    err = read_livers_file(in, &livers);
    fclose(in);
    if (err) {
        destroy_stack(&undoStack);
        destroy(&filename);
        return err;
    }

    printf("Please input your command (or type 'help' for info).\n");
    while (1) {
        switch (state) {
            case COMMAND_WAIT:
                err = wait_command(&cmd);
                if (err) {
                    destroy_stack(&undoStack);
                    destroy(&filename);
                    destroy_list(&livers);
                    return 0;
                }

                state = COMMAND_HANDLE;
                break;
            case COMMAND_HANDLE:
                err = handle_command(cmd, &livers, &filename, &undoStack);
                if (err == EOF) {
                    destroy_stack(&undoStack);
                    destroy(&filename);
                    destroy_list(&livers);
                    return 0;
                }

                if (err) {
                    destroy_stack(&undoStack);
                    destroy(&filename);
                    destroy_list(&livers);
                    return err;
                }

                state = COMMAND_WAIT;
                break;
            default:
                destroy_stack(&undoStack);
                destroy(&filename);
                destroy_list(&livers);
                return throw_err(INCORRECT_OPTION);
        }
    }
}

int wait_command(Command *result) {
    Array buf;
    int err = create_arr(5, &buf);
    if (err)
        return err;

    while (1) {
        printf("> %s", "\0");
        overfscanf(stdin, " %S", &buf);
        printf("\n");

        if (is_str_equal(buf.val, "^Z")) {
            destroy(&buf);
            return 1;
        } else if (is_str_equal(buf.val, "help")) {
            *result = HELP;
            break;
        } else if (is_str_equal(buf.val, "add")) {
            *result = ADD;
            break;
        } else if (is_str_equal(buf.val, "remove")) {
            *result = REMOVE;
            break;
        } else if (is_str_equal(buf.val, "edit")) {
            *result = EDIT;
            break;
        } else if (is_str_equal(buf.val, "undo")) {
            *result = UNDO;
            break;
        } else if (is_str_equal(buf.val, "search")) {
            *result = SEARCH;
            break;
        } else if (is_str_equal(buf.val, "export")) {
            *result = EXPORT;
            break;
        } else if (is_str_equal(buf.val, "path")) {
            *result = CHANGE_EXPORT_PATH;
            break;
        } else if (is_num(buf.val[0]) && buf.length == 1) {
            *result = buf.val[0] - '0' - 1;
            break;
        } else {
            printf("Incorrect command. Please try again or use 'help' command.\n");
        }
        reset(&buf);
    }

    destroy(&buf);

    return 0;
}

int handle_command(Command cmd, LiverList **livers, Array *export_path, UndoStack *undoStack) {
    int param = 0;
    int err = 0;

    String searchString;
    SearchParameter parameter;

    switch (cmd) {
        case HELP:
            help_cmd();
            break;
        case ADD:
            err = add_liver(livers, undoStack);

            if (!err || err == INCORRECT_INPUT_DATA)
                return 0;
            else
                return err;

            break;
        case REMOVE:
            printf("To remove a Liver, you have to find him using search.\n");
            err = wait_param(cmd, &param);
            if (err == EOF)
                return err;

            if (err || param < 0 || param > 5) {
                throw_err(INCORRECT_OPTION);
                break;
            }

            err = wait_search_param(&parameter, param);
            if (err)
                return err;

            err = delete_liver(livers, param, parameter, undoStack);

            if (param >= SURNAME && param <= BIRTHDATE)
                destroy_str(&parameter.str);

            if (!err || err == INCORRECT_INPUT_DATA || err == OUT_OF_BOUNDS)
                return 0;
            else
                return err;

            break;
        case EDIT:
            printf("To edit a Liver, you have to find him using search.\n");
            err = wait_param(cmd, &param);
            if (err == EOF)
                return err;

            if (err || param < 0 || param > 5) {
                throw_err(INCORRECT_OPTION);
                break;
            }

            err = wait_search_param(&parameter, param);
            if (err)
                return err;

            err = edit_liver(livers, param, parameter, undoStack);

            if (param >= SURNAME && param <= BIRTHDATE)
                destroy_str(&parameter.str);

            if (!err || err == INCORRECT_INPUT_DATA || err == OUT_OF_BOUNDS)
                return 0;
            else
                return err;

            break;
        case SEARCH:
            err = wait_param(cmd, &param);
            if (err == EOF)
                return err;

            if (err || param < 0 || param > 5) {
                throw_err(INCORRECT_OPTION);
                break;
            }

            err = wait_search_param(&parameter, param);
            if (err)
                return err;

            LiverList *result = {};

            int found = liver_search(livers, param, parameter, &result);

            if (param >= SURNAME && param <= BIRTHDATE)
                destroy_str(&parameter.str);

            if (!found) {
                printf("No occurrences were found.\n");
                destroy_list(&result);
                return 0;
            }

            printf("Found Livers:\n");

            write_livers(stdout, result);

            destroy_list(&result);
            break;
        case CHANGE_EXPORT_PATH:
            change_export_path(export_path);
            break;
        case EXPORT:
            if (export_path->length == 0) {
                printf("No path for export file was provided.\n");
                return 0;
            }

            FILE *out = fopen(export_path->val, "w");
            if (!out)
                return throw_err(FILE_ERROR);

            write_livers(out, *livers);

            fclose(out);
            break;
        case UNDO:
            err = undo_cmd(livers, undoStack);
            if (err)
                return err;
            break;
        default:
            throw_err(INCORRECT_OPTION);
            return 0;
    }

    return 0;
}

int wait_param(Command cmd, int *param) {
    cmd_description(cmd);

    printf("Please enter function parameter: \n");

    int scan_read = scanf("%d", param);

    if (scan_read == EOF) {
        return EOF;
    } else if (!scan_read) {
        printf("Incorrect parameter. Please try again.\n");
        return 1;
    } else {
        *param -= 1;
        return 0;
    }
}

int wait_search_param(SearchParameter *searchParam, SearchCriteria criteria) {
    printf("Please enter string/value to search for: \n");
    int scan_read = 0;

    if (criteria >= SURNAME && criteria <= BIRTHDATE) {
        char buf[1000];

        scan_read = scanf("%s", buf);

        create_str(&searchParam->str, buf);
    } else if (criteria == SEX) {
        fgetc(stdin);
        char sex;

        scan_read = scanf("%c", &sex);

        searchParam->sex = sex;
    } else if (criteria == SALARY) {
        float salary;

        scan_read = scanf("%f", &salary);

        searchParam->salary = salary;
    }

    if (scan_read == EOF) {
        return 1;
    } else if (!scan_read) {
        throw_err(INCORRECT_ARGUMENTS);
        return 0;
    }

    return 0;
}

void cmd_description(Command cmd) {
    int level = 1;
    int j = 1;

    char *cmd_descriptions[][10] = {
            {"'help' - Print all available commands and their options", NULL},
            {"'add' - Add Liver",                                       NULL},
            {"'remove' - Remove Liver by parameters",     "Surname", "Name", "Patronymic", "Birthdate", "Sex", "Salary", NULL},
            {"'edit' - Edit information about the Liver", "Surname", "Name", "Patronymic", "Birthdate", "Sex", "Salary", NULL},
            {"'search' - Search Liver by parameters",     "Surname", "Name", "Patronymic", "Birthdate", "Sex", "Salary", NULL},
            {"'path' - Change export file path",                        NULL},
            {"'export' - Export information about Livers to the file",  NULL},
            {"'undo' - Undo half of the previous modifications",        NULL}
    };

    printf("%*d. %s.\n", level * 2, cmd + 1, cmd_descriptions[cmd][0]);
    level++;
    while (cmd_descriptions[cmd][j] != NULL) {
        printf("%*d) %s.\n", level * 2, j, cmd_descriptions[cmd][j]);

        j++;
    }

}

void help_cmd() {
    int cmd_amount = 8;

    printf("Available commands (you can use them by typing numbers corresponding or command strings):\n");
    for (int i = 1; i <= cmd_amount; ++i) {
        cmd_description(i - 1);
    }
}


int check_latin_letters(Array a) {
    for (int i = 0; i < a.length; ++i) {
        if (!is_letter(a.val[i]))
            return 1;
    }

    return 0;
}

int add_liver(LiverList **list, UndoStack *undoStack) {
    int err;
    int cur_scan;

    Array temp;
    err = create_arr(5, &temp);
    if (err)
        return err;

    printf("Surname: ");
    cur_scan = overfscanf(stdin, "%S", &temp);

    if (cur_scan < 1 || check_latin_letters(temp)) {
        destroy(&temp);

        return throw_err(INCORRECT_INPUT_DATA);
    }

    String surname;
    err = create_str(&surname, temp.val);
    if (err) {
        destroy(&temp);
        return err;
    }

    reset(&temp);

    printf("Name: ");
    cur_scan = overfscanf(stdin, "%S", &temp);

    if (cur_scan < 1 || check_latin_letters(temp)) {
        destroy(&temp);
        destroy_str(&surname);

        return throw_err(INCORRECT_INPUT_DATA);
    }

    String name;
    err = create_str(&name, temp.val);
    if (err) {
        destroy(&temp);
        destroy_str(&surname);
        return err;
    }

    reset(&temp);

    printf("Patronymic: ");
    err = read_whole_input(&temp);

    String patronymic;

    if (temp.length > 0) {

        if (err || check_latin_letters(temp)) {
            destroy(&temp);
            destroy_str(&surname);
            destroy_str(&name);

            return throw_err(INCORRECT_INPUT_DATA);
        }

        err = create_str(&patronymic, temp.val);
        if (err) {
            destroy_str(&surname);
            destroy_str(&name);
            return err;
        }
    } else {
        err = create_str(&patronymic, "");
        if (err) {
            destroy_str(&surname);
            destroy_str(&name);
            return err;
        }
    }

    destroy(&temp);

    char temp_birth[11], buf[100];

    printf("Date of birth (dd.mm.yyyy): ");
    cur_scan = scanf("%10s", temp_birth);

    err = skip_to_end_line();
    if (err) {
        destroy_str(&surname);
        destroy_str(&name);
        destroy_str(&patronymic);
        return err;
    }

    String birthdate;
    err = create_str(&birthdate, temp_birth);
    if (err) {
        destroy_str(&surname);
        destroy_str(&name);
        destroy_str(&patronymic);
        return err;
    }

    Time time;

    if (cur_scan < 1 || parse_time(&birthdate, &time)) {
        destroy_str(&surname);
        destroy_str(&name);
        destroy_str(&patronymic);
        destroy_str(&birthdate);
        return throw_err(INCORRECT_INPUT_DATA);
    }

    char sex;

    printf("Sex (M or W): ");
    cur_scan = scanf("%c", &sex);
    err = skip_to_end_line();
    if (err) {
        destroy_str(&surname);
        destroy_str(&name);
        destroy_str(&patronymic);
        return err;
    }

    if (cur_scan < 1 || (sex != 'W' && sex != 'M')) {
        destroy_str(&surname);
        destroy_str(&name);
        destroy_str(&patronymic);
        destroy_str(&birthdate);
        return throw_err(INCORRECT_INPUT_DATA);
    }

    float salary;

    printf("Salary (positive real number): ");
    cur_scan = scanf("%f", &salary);
    err = skip_to_end_line();
    if (err) {
        destroy_str(&surname);
        destroy_str(&name);
        destroy_str(&patronymic);
        return err;
    }

    if (cur_scan < 1 || salary < 0) {
        destroy_str(&surname);
        destroy_str(&name);
        destroy_str(&patronymic);
        destroy_str(&birthdate);
        return throw_err(INCORRECT_INPUT_DATA);
    }

    Liver liver = {surname, name, patronymic, birthdate, sex, salary};

    err = insert_list_condition(list, liver, compare_age);
    if (err) {
        destroy_liver(&liver);
        return err;
    }

    printf("Liver successfully added!\n");

//    destroy_liver(&liver);
//    if (err)
//        return err;

    Change newChange = {ADD, NULL, &liver};

    err = push_stack(undoStack, newChange);
    destroy_liver(&liver);
    if (err)
        return err;

    return 0;
}

int delete_liver(LiverList **list, SearchCriteria criteria, SearchParameter parameter, UndoStack *undoStack) {
    LiverList *res = {};
    int read;

    if (!(read = liver_search(list, criteria, parameter, &res))) {
        printf("No livers with this parameter were found.\n");

        destroy_list(&res);
        return 0;
    }

    printf("Found livers:");
    write_livers(stdout, res);

    printf("Choose Liver to delete (type number of occurrence): ");

    int i;

    if (!scanf("%d", &i) || i < 1 || i > read) {
        destroy_list(&res);
        return throw_err(INCORRECT_INPUT_DATA);
    }

    LiverList *cur = res;

    for (int j = 1; j < i; ++j) {
        if (!cur) {
            destroy_list(&res);
            return throw_err(OUT_OF_BOUNDS);
        }

        cur = cur->next;
    }

    Change newChange = {REMOVE, &cur->val, NULL};

    int err = push_stack(undoStack, newChange);
    if (err) {
        destroy_list(&res);
        return err;
    }

    LiverList *deleting;
    find_liver(list, cur->val, &deleting);

    err = delete_node(list, deleting);
    destroy_list(&res);
    if (err)
        return err;

    printf("Liver was deleted successfully.\n");

    return 0;
}

int edit_liver(LiverList **list, SearchCriteria criteria, SearchParameter parameter, UndoStack *undoStack) {
    LiverList *res = {};
    int read;
    int err;

    if (!(read = liver_search(list, criteria, parameter, &res))) {
        printf("No livers with this parameter were found.\n");

        destroy_list(&res);
        return 0;
    }

    printf("Found livers:\n");
    write_livers(stdout, res);

    printf("Choose Liver to edit (type number of occurrence): ");

    int i;

    if (!scanf("%d", &i) || i < 1 || i > read) {
        destroy_list(&res);
        return throw_err(INCORRECT_INPUT_DATA);
    }

    LiverList *cur = res;

    for (int j = 1; j < i; ++j) {
        if (!cur) {
            destroy_list(&res);
            return throw_err(OUT_OF_BOUNDS);
        }

        cur = cur->next;
    }

    LiverList *editing;
    find_liver(list, cur->val, &editing);

    Liver changingLiver = editing->val, oldLiver;

    copy_liver(&oldLiver, &changingLiver);

    destroy_list(&res);

    printf("\n");

    cmd_description(EDIT);

    printf("\n");

    printf("Choose parameter to edit (number): ");

    if (!scanf("%d", &i) || i < 1 || i > 6) {
        destroy_liver(&oldLiver);
        return throw_err(INCORRECT_OPTION);
    }

    i--;

    Array temp;
    String edit_value;

    err = create_arr(5, &temp);
    if (err) {
        destroy_liver(&oldLiver);
        return err;
    }

    if (i >= SURNAME && i <= BIRTHDATE) {
        printf("Choose new string value: ");
        fgetc(stdin);

        err = read_whole_input(&temp);
        if (err) {
            destroy_liver(&oldLiver);
            destroy(&temp);
            return err;
        }
    }

    err = create_str(&edit_value, temp.val);
    destroy(&temp);
    if (err) {
        destroy_liver(&oldLiver);
        return err;
    }

    Time time;

    switch (i) {
        case SURNAME:
            copystr(&changingLiver.surname, &edit_value);
            break;
        case NAME:
            copystr(&changingLiver.name, &edit_value);
            break;
        case PATRONYMIC:
            copystr(&changingLiver.patronymic, &edit_value);
            break;
        case BIRTHDATE:
            if (parse_time(&edit_value, &time)) {
                destroy_liver(&oldLiver);
                destroy_str(&edit_value);
                return throw_err(INCORRECT_INPUT_DATA);
            }

            copystr(&changingLiver.birthdate, &edit_value);
            break;
        case SEX:
            printf("Enter new sex (M or W): ");

            char sex;

            err = scanf("%c", &sex);
            if (!err || sex != 'W' && sex != 'M') {
                destroy_liver(&oldLiver);
                destroy_str(&edit_value);
                return throw_err(INCORRECT_INPUT_DATA);
            }

            changingLiver.sex = sex;
            break;
        case SALARY:
            printf("Enter new salary (positive real number): ");

            float salary;

            err = scanf("%f", &salary);
            if (!err || salary < 0) {
                destroy_liver(&oldLiver);
                destroy_str(&edit_value);
                return throw_err(INCORRECT_INPUT_DATA);
            }

            changingLiver.mean_salary = salary;
            break;
        default:
            destroy_liver(&oldLiver);
            destroy_str(&edit_value);
            return throw_err(INCORRECT_OPTION);
    }

    destroy_str(&edit_value);

    Change newChange = {EDIT, &oldLiver, &changingLiver};

    err = push_stack(undoStack, newChange);
    if (err)
        return err;

    destroy_liver(&oldLiver);

    editing->val = changingLiver;

    printf("Liver was edited successfully.\n");

    return 0;
}

int read_livers_file(FILE *in, LiverList **list) {
    if (!in)
        return throw_err(FILE_ERROR);

    int cur;
    int err;

    while (!seek_char(&in, &cur) && cur > 0) {
        Array surname, name, patronymic;

        err = create_arr(5, &surname);
        if (err)
            return err;

        err = append(&surname, (char) cur);
        if (err) {
            destroy(&surname);
            return err;
        }

        err = create_arr(5, &name);
        if (err) {
            destroy(&surname);
            return err;
        }

        err = create_arr(5, &patronymic);
        if (err) {
            destroy(&surname);
            destroy(&name);
            return err;
        }

        overfscanf(in, "%S %S %S", &surname, &name, &patronymic);

        Time time;
        int is_birthdate = parse_time_arr(&patronymic, &time);

        if (surname.length == 0 || name.length == 0 || check_latin_letters(surname) || check_latin_letters(name) ||
            (check_latin_letters(patronymic) && is_birthdate)) {
            destroy(&surname);
            destroy(&name);
            destroy(&patronymic);

            return throw_err(INCORRECT_INPUT_DATA);
        }

        is_birthdate = !is_birthdate;

        int scan_read = 0;

        char sex;
        char tempbirth[11];
        String birthdate = {};
        err = create_str(&birthdate, "");
        if (err) {
            destroy(&surname);
            destroy(&name);
            destroy(&patronymic);
            return err;
        }

        float salary;

        if (!is_birthdate) {
            scan_read = fscanf(in, "%10s", tempbirth);

            destroy_str(&birthdate);

            err = create_str(&birthdate, tempbirth);

            if (err || scan_read != 1 || parse_time(&birthdate, &time)) {
                destroy(&surname);
                destroy(&name);
                destroy(&patronymic);

                return throw_err(INCORRECT_INPUT_DATA);
            }
        } else {
            destroy_str(&birthdate);
            err = create_str(&birthdate, patronymic.val);
            reset(&patronymic);
        }

        scan_read = fscanf(in, " %c %f", &sex, &salary);
        if (err || scan_read != 2 || (sex != 'W' && sex != 'M') || salary < 0) {
            destroy(&surname);
            destroy(&name);
            destroy(&patronymic);

            return throw_err(INCORRECT_INPUT_DATA);
        }

        String name_str, surname_str, patronymic_str;

        err = create_str(&name_str, name.val);
        destroy(&name);
        if (err) {
            destroy(&surname);
            if (!is_birthdate)
                destroy(&patronymic);

            return err;
        }

        err = create_str(&surname_str, surname.val);
        destroy(&surname);
        if (err) {
            if (!is_birthdate)
                destroy(&patronymic);

            return err;
        }

        err = create_str(&patronymic_str, patronymic.val);
        destroy(&patronymic);
        if (err)
            return err;

        Liver liver = {surname_str, name_str, patronymic_str, birthdate, sex, salary};

        insert_list_condition(list, liver, compare_age);

        destroy_liver(&liver);
    }

    return 0;
}

int change_export_path(Array *initial_path) {
    printf("Enter new export path (filename): ");

    reset(initial_path);

    int err = overfscanf(stdin, "%S", initial_path);
    if (!err) {
        return throw_err(INCORRECT_INPUT_DATA);
    }

    return 0;
}

int undo_cmd(LiverList **list, UndoStack *stack) {
    int err;

    printf("%d actions were undone.\n", (stack->length + 1) / 2);

    for (int i = 0; i < (stack->length + 1) / 2; ++i) {
        Change *change = pop_stack(stack);
        LiverList *found;

        switch (change->cmd) {
            case ADD:
                err = find_liver(list, *change->changed, &found);
                if (err)
                    return err;

                destroy_liver(&found->val);

                delete_node(list, found);

                break;
            case REMOVE:
                err = insert_list_condition(list, *change->old, compare_age);
                if (err)
                    return err;

                break;
            case EDIT:
                err = find_liver(list, *change->changed, &found);
                if (err)
                    return err;

                destroy_liver(&found->val);
                copy_liver(&found->val, change->old);
                break;
            default:
                return throw_err(INCORRECT_OPTION);
        }

        if (change->old)
            destroy_liver(change->old);
        if (change->changed)
            destroy_liver(change->changed);

        free(change->old);
        free(change->changed);
    }

    destroy_stack(stack);

    err = create_stack(stack);
    if (err)
        return err;

    return 0;
}

