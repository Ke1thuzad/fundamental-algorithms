#include "main.h"
#include "../task7/main.h"
#include "../task5/main.h"

int dialog_manager() {
    DialogFSM state = COMMAND_WAIT;
    Command cmd;

    Post post;

    int err;

    while (1) {
        err = init_post(&post);
        printf("\n");
        if (!err) {
            break;
        }
    }

    printf("Please input your command (or type 'help' for info).\n");
    while (1) {
        switch (state) {
            case COMMAND_WAIT:
                err = wait_command(&cmd);
                if (err) {
                    destroy_post(&post);
//                    destroy_stud(&students);
                    return 0;
                }

                state = COMMAND_HANDLE;
                break;
            case COMMAND_HANDLE:
                err = handle_command(cmd, &post);
                if (err == EOF) {
                    destroy_post(&post);
//                    destroy_stud(&students);
                    return 0;
                }

                if (err) {
                    destroy_post(&post);
//                    destroy_stud(&students);
                    return err;
                }

                state = COMMAND_WAIT;
                break;
            default:
                destroy_post(&post);
//                destroy_stud(&students);
                return throw_err(INCORRECT_OPTION);
        }
    }
}

int init_post(Post *post) {
    int scan_read = 0, cur_read = 0;

    Array post_index, building, city, street;

    int err = create_arr(STANDARD_CAPACITY, &post_index);
    if (err)
        return err;

    err = create_arr(STANDARD_CAPACITY, &building);
    if (err) {
        destroy(&post_index);
        return err;
    }

    err = create_arr(STANDARD_CAPACITY, &city);
    if (err) {
        destroy(&post_index);
        destroy(&building);
        return err;
    }

    err = create_arr(STANDARD_CAPACITY, &street);
    if (err) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        return err;
    }

    int apartment, house;

    printf("Enter post address details:\n");
    printf("Post Index (6 digits): ");
    scan_read += (cur_read = overfscanf(stdin, " %S", &post_index));
//    fseek(stdin, 1, SEEK_CUR);

    if (cur_read < 1) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        destroy(&street);

        return throw_err(INCORRECT_INPUT_DATA);
    }
    printf("City: ");
    scan_read += (cur_read = overfscanf(stdin, " %S", &city));
//    fseek(stdin, 1, SEEK_CUR);

    if (cur_read < 1) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        destroy(&street);

        return throw_err(INCORRECT_INPUT_DATA);
    }
    printf("Street: ");
    scan_read += (cur_read = overfscanf(stdin, " %S", &street));
//    fseek(stdin, 1, SEEK_CUR);

    if (cur_read < 1) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        destroy(&street);

        return throw_err(INCORRECT_INPUT_DATA);
    }

    printf("Building: ");
    scan_read += (cur_read = overfscanf(stdin, " %S", &building));
//    fseek(stdin, 1, SEEK_CUR);

    if (cur_read < 1) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        destroy(&street);

        return throw_err(INCORRECT_INPUT_DATA);
    }

    printf("Block (natural number): ");
    scan_read += (cur_read = scanf("%d", &house));
    char buf[1000];
    fgets(buf, 1000, stdin);
//    fseek(stdin, 1, SEEK_CUR);

    if (cur_read < 1) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        destroy(&street);

        return throw_err(INCORRECT_INPUT_DATA);
    }

    printf("Apartment (natural number): ");
    scan_read += (cur_read = scanf("%d", &apartment));
    fgets(buf, 1000, stdin);

    if (cur_read < 1) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        destroy(&street);

        return throw_err(INCORRECT_INPUT_DATA);
    }

    if (scan_read != 6) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        destroy(&street);

        return throw_err(INCORRECT_INPUT_DATA);
    }

    Address *addr = (Address *) malloc(sizeof(Address));
    if (!addr) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        destroy(&street);

        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    err = create_address(addr, post_index.val, building.val, city.val, street.val, apartment, house);

    destroy(&post_index);
    destroy(&building);
    destroy(&city);
    destroy(&street);

    if (err) {
        free(addr);
        return err;
    }

    create_post(post, addr);

    printf("Successfully initialized post!\n");
    return 0;
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
        } else if (is_str_equal(buf.val, "print")) {
            *result = PRINT;
            break;
        } else if (is_str_equal(buf.val, "search")) {
            *result = SEARCH;
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

int handle_command(Command cmd, Post *post) {
    int param = 0;
    int err = 0;

    switch (cmd) {
        case HELP:
            help_cmd();
            break;
        case ADD:
            err = add_mail_cmd(post);
            if (err)
                return 0;

            break;
        case REMOVE:
            // wtf?
            String stringID;
            err = wait_search_param(&stringID, PATRONYMIC);

            if (err)
                return err;

            err = delete_post_mail(post, stringID);

            if (err)
                printf("Couldn't find any mail with this ID to delete.\n");
            else
                printf("Successfully deleted mail with ID: %s.\n", stringID.val);

            destroy_str(&stringID);

            break;
        case PRINT:
            print_cmd(*post);

            break;
        case SEARCH:
            err = wait_param(cmd, &param);
            if (err == EOF)
                return err;

            if (err)
                break;

            Mail *found = (Mail *) malloc(sizeof(Mail) * post->length);
            int index = 0;

            if (param != 0) {
                if (param == 1) {
                    search_mail_in_time(post, found, &index);
                } else if (param == 2) {
                    search_mail_delayed(post, found, &index);
                } else {
                    throw_err(INCORRECT_OPTION);
                    return 0;
                }

                for (int i = 0; i < index; ++i) {
                    print_mail(found[i]);
                }

                free(found);
                return 0;
            }

            String searchParameter;

            err = wait_search_param(&searchParameter, PATRONYMIC);

            if (err) {
                free(found);
                return EOF;
            }

            err = search_mail_id(post, searchParameter, &found, &index);
            destroy_str(&searchParameter);

            if (err) {
                printf("No occurrences were found.\n");
                free(found);
                return 0;
            }

            print_mail(*found);

            free(found);
            break;
        default:
            return throw_err(INCORRECT_OPTION);
    }

    return 0;
}

int wait_param(Command cmd, int *param) {
    switch (cmd) {
        case SEARCH:
            cmd_description(SEARCH);
            break;
        default:
            return throw_err(INCORRECT_OPTION);
    }


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
    printf("Please enter parameter to search for: \n");
    int scan_read = 0;
    char buf[1000];

    scan_read = scanf("%s", buf);


    if (scan_read == EOF) {
        return 1;
    } else if (!scan_read) {
        throw_err(INCORRECT_ARGUMENTS);
        return 0;
    } else {
        create_str(searchParam, buf);
        return 0;
    }
}

void cmd_description(Command cmd) {
    int level = 1;
    int j = 1;

    char *cmd_descriptions[][10] = {
            {"'help' - Print all available commands and their options", NULL},
            {"'add' - Add Mail to the Post",                            NULL},
            {"'remove' - Remove Mail from the Post (by ID)",            NULL},
            {"'print' - Print information about Mails",                 NULL},
            {"'search' - Search Mail by parameters", "ID", "Delivered", "Delayed", NULL}
    };

    printf("%*d. %s.\n", level * 2, cmd + 1, cmd_descriptions[cmd][0]);
    level++;
    while (cmd_descriptions[cmd][j] != NULL) {
        printf("%*d) %s.\n", level * 2, j, cmd_descriptions[cmd][j]);

        j++;
    }

}

void help_cmd() {
    int cmd_amount = 5;

    printf("Available commands (you can use them by typing numbers corresponding or command strings):\n");
    for (int i = 1; i <= cmd_amount; ++i) {
        cmd_description(i - 1);
    }
}

void print_cmd(Post post) {
    qsort(post.mails, post.length, sizeof(Mail), compare_mail);

    printf("Current mails in the post:\n");

    for (int i = 0; i < post.length; ++i) {
        print_mail(post.mails[i]);
    }
}

int add_mail_cmd(Post *post) {
    int scan_read = 0, cur_read = 0;

    char creation_date_p1[15], creation_date_p2[15];
    char delivery_date_p1[15], delivery_date_p2[15];

    Array post_index, building, city, street, id;

    int err = create_arr(STANDARD_CAPACITY, &post_index);
    if (err)
        return err;

    err = create_arr(STANDARD_CAPACITY, &building);
    if (err) {
        destroy(&post_index);
        return err;
    }

    err = create_arr(STANDARD_CAPACITY, &city);
    if (err) {
        destroy(&post_index);
        destroy(&building);
        return err;
    }

    err = create_arr(STANDARD_CAPACITY, &street);
    if (err) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        return err;
    }

    err = create_arr(STANDARD_CAPACITY, &id);
    if (err) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        destroy(&street);
        return err;
    }

    int apartment, house;
    float weight;

    printf("Enter mail details:\n");

    printf("Post Index (6 digits): ");
    scan_read += (cur_read = overfscanf(stdin, " %S", &post_index));
    if (cur_read < 1) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        destroy(&street);
        destroy(&id);

        return throw_err(INCORRECT_INPUT_DATA);
    }
    printf("City: ");
    scan_read += (cur_read = overfscanf(stdin, " %S", &city));
    if (cur_read < 1) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        destroy(&street);
        destroy(&id);

        return throw_err(INCORRECT_INPUT_DATA);
    }
    printf("Street: ");
    scan_read += (cur_read = overfscanf(stdin, " %S", &street));
    if (cur_read < 1) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        destroy(&street);
        destroy(&id);

        return throw_err(INCORRECT_INPUT_DATA);
    }

    printf("Building: ");
    scan_read += (cur_read = overfscanf(stdin, " %S", &building));
    if (cur_read < 1) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        destroy(&street);
        destroy(&id);

        return throw_err(INCORRECT_INPUT_DATA);
    }

    printf("Block (natural number): ");
    scan_read += (cur_read = scanf("%d", &house));
    char buf[1000];
    fgets(buf, 1000, stdin);

    if (cur_read < 1) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        destroy(&street);
        destroy(&id);

        return throw_err(INCORRECT_INPUT_DATA);
    }

    printf("Apartment (natural number): ");
    scan_read += (cur_read = scanf("%d", &apartment));
    fgets(buf, 1000, stdin);

    if (cur_read < 1) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        destroy(&street);
        destroy(&id);

        return throw_err(INCORRECT_INPUT_DATA);
    }
    printf("Weight (positive real number): ");
    scan_read += (cur_read = scanf("%f", &weight));
    fgets(buf, 1000, stdin);

    if (cur_read < 1) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        destroy(&street);
        destroy(&id);

        return throw_err(INCORRECT_INPUT_DATA);
    }
    printf("ID (14 digits): ");
    scan_read += (cur_read = overfscanf(stdin, " %S", &id));

    if (cur_read < 1) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        destroy(&street);
        destroy(&id);

        return throw_err(INCORRECT_INPUT_DATA);
    }
    printf("Creation Date (dd:mm:yyyy hh:mm:ss): ");
    scan_read += (cur_read = scanf("%10s %8s", creation_date_p1, creation_date_p2));
    fgets(buf, 1000, stdin);

    if (cur_read < 2) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        destroy(&street);
        destroy(&id);

        return throw_err(INCORRECT_INPUT_DATA);
    }
    printf("Delivery Date (dd:mm:yyyy hh:mm:ss): ");
    scan_read += (cur_read = scanf("%10s %8s", delivery_date_p1, delivery_date_p2));
    fgets(buf, 1000, stdin);

    if (cur_read < 2) {
        destroy(&post_index);
        destroy(&building);
        destroy(&city);
        destroy(&street);
        destroy(&id);

        return throw_err(INCORRECT_INPUT_DATA);
    }

    if (scan_read != 12)
        return throw_err(INCORRECT_INPUT_DATA);

    Address *addr = malloc(sizeof(Address));
    if (!addr)
        return throw_err(MEMORY_NOT_ALLOCATED);

    err = create_address(addr, post_index.val, building.val, city.val, street.val, apartment, house);


    destroy(&post_index);
    destroy(&building);
    destroy(&city);
    destroy(&street);

    if (err) {
        destroy(&id);
        return err;
    }

    char creation_date[30] = "";
    char delivery_date[30] = "";

    string_concat(creation_date, creation_date_p1);
    string_concat(creation_date, " ");
    string_concat(creation_date, creation_date_p2);

    string_concat(delivery_date, delivery_date_p1);
    string_concat(delivery_date, " ");
    string_concat(delivery_date, delivery_date_p2);

    Mail mail;
    err = create_mail(&mail, *addr, weight, id.val, creation_date, delivery_date);

    destroy_address(addr);
    free(addr);
    destroy(&id);

    if (err)
        return err;


    err = append_post(post, mail);
    destroy_mail(&mail);
    if (err)
        return err;


    printf("Mail added successfully.\n");
    return 0;
}


