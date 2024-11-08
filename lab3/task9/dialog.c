#include "main.h"

int dialog_manager(FILE *in, char **argv, int argc) {
    Node *root = NULL;
    int err;

    err = parse_file_seps(in, &root, argv, argc);
    if (err) {
        destroy_tree(root);
        return err;
    }

    fclose(in);

    print_tree(root, 0);

    DialogFSM state = COMMAND_WAIT;
    Command cmd;

    while (1) {
        switch (state) {
            case COMMAND_WAIT:
                if (wait_command(&cmd)) {
                    destroy_tree(root);
                    return 0;
                }

                state = COMMAND_HANDLE;
                break;
            case COMMAND_HANDLE:
                err = handle_command(cmd, &root);
//                if (err) {
//                    destroy_tree(root);
//                    return err;
//                }

                state = COMMAND_WAIT;
                break;
            default:
                destroy_tree(root);
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
        } else if (is_str_equal(buf.val, "print")) {
            *result = PRINT;
            break;
        } else if (is_str_equal(buf.val, "search")) {
            *result = SEARCH;
            break;
        } else if (is_str_equal(buf.val, "most_frequent")) {
            *result = N_MOST_FREQUENT;
            break;
        } else if (is_str_equal(buf.val, "edges")) {
            *result = EDGES;
            break;
        } else if (is_str_equal(buf.val, "depth")) {
            *result = DEPTH;
            break;
        } else if (is_str_equal(buf.val, "save")) {
            *result = SAVE;
            break;
        } else if (is_str_equal(buf.val, "load")) {
            *result = LOAD;
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

int handle_command(Command cmd, Node **root) {
    int param = 0;
    int err = 0;

    String searchString;
    NodeList *most_frequent = NULL;
    Node *result = NULL;
    int depth;
    Array path;

    switch (cmd) {
        case HELP:
            help_cmd();
            break;
        case PRINT:
            print_tree(*root, 0);
            break;
        case SEARCH:
            printf("Enter word to search: ");
            err = read_whole_input_str(&searchString);
            if (err && searchString.length > 0) {
                destroy_str(&searchString);
                return err;
            }

            if (search_word(*root, searchString, &result)) {
                printf("Word '%s' not found.\n", searchString.val);
            } else {
                printf("Word '%s' found with frequency %d.\n", searchString.val, result->frequency);
            }

            destroy_str(&searchString);
            break;
        case N_MOST_FREQUENT:
            printf("Enter number of most frequent words to display: ");
            err = scanf("%d", &param);
            if (!err)
                return throw_err(INCORRECT_INPUT_DATA);

            err = find_most_frequent_words(*root, &most_frequent);
            if (err)
                return err;

            NodeList *cur = most_frequent;

            for (int i = 0; i < param && cur; ++i) {
                printf("\tWord '%s' found with frequency %d.\n", cur->val->val.val, cur->val->frequency);

                cur = cur->next;
            }

            destroy_list(&most_frequent);
            break;
        case EDGES:
            printf("Longest word: %s\n", find_longest_word(*root)->val.val);
            printf("Shortest word: %s\n", find_shortest_word(*root)->val.val);
            break;
        case DEPTH:
            tree_depth(*root, &depth);

            printf("Depth of the BST: %d\n", depth);
            break;
        case SAVE:
            printf("Enter file path to save the tree: ");
            err = create_arr(5, &path);
            if (err)
                return err;

            err = read_whole_input(&path);
            if (err) {
                destroy(&path);
                return err;
            }

            save_tree_to_file(*root, path.val);
            destroy(&path);
            break;
        case LOAD:
            printf("Enter file path to load the tree: ");
            err = create_arr(5, &path);
            if (err)
                return err;

            err = read_whole_input(&path);
            if (err) {
                destroy(&path);
                return err;
            }

            err = load_tree_from_file(path.val, root);
            destroy(&path);
            if (err)
                return err;

//            print_tree(*root, 0);
            break;
        default:
            return throw_err(INCORRECT_OPTION);
    }

    return 0;
}

void cmd_description(Command cmd) {
    int level = 1;
    int j = 1;

    char *cmd_descriptions[][10] = {
            {"'help' - Print all available commands and their options",                         NULL},
            {"'print' - Print whole tree",                                                      NULL},
            {"'search' - Search for word and its frequency",                                    NULL},
            {"'most_frequent' - Find the most frequent word in the text",                       NULL},
            {"'edges' - Find the longest and shortest words and their frequencies accordingly", NULL},
            {"'depth' - Find depth of the BST",                                                 NULL},
            {"'save' - Save tree to the file",                                                  NULL},
            {"'load' - Read tree from the file",                                                NULL},
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

int read_whole_input_str(String *result) {
    int err;

    Array temp;
    err = create_arr(5, &temp);
    if (err)
        return err;

    err = read_whole_input(&temp);
    if (err) {
        destroy(&temp);
        return err;
    }

    err = create_str(result, temp.val);
    destroy(&temp);
    if (err)
        return err;

    return 0;
}

Node *find_longest_word(Node *root) {
    if (!root)
        return NULL;

    Node *cur = root;
    while (cur->right) {
        cur = cur->right;
    }

    return cur;
}

Node *find_shortest_word(Node *root) {
    if (!root)
        return NULL;

    Node *cur = root;
    while (cur->left) {
        cur = cur->left;
    }

    return cur;
}

int parse_file_seps(FILE *in, Node **root, char **argv, int argc) {
    int err;
    int i = 2;
    int c;

    String inp;
    err = create_str(&inp, "");
    if (err)
        return err;

    while ((c = fgetc(in)) > 0) {
        if (i < argc && ((char) c) == argv[i][0]) {
            if (inp.length > 0) {
                err = insert_tree(root, inp);
                if (err) {
                    destroy_str(&inp);
                    return err;
                }

                reset_str(&inp);
                i++;
            }
        } else {
            err = append_str(&inp, (char) c);
            if (err) {
                destroy_str(&inp);
                return err;
            }
        }
    }

    if (inp.length > 0)
        err = insert_tree(root, inp);

    destroy_str(&inp);

    return err;
}

int save_tree_to_file(Node *root, const char *filepath) {
    FILE *file = fopen(filepath, "w");
    if (!file)
        return throw_err(FILE_ERROR);

    save_tree_nodes(root, file);

    fclose(file);

    return 0;
}

void save_tree_nodes(Node *root, FILE *out) {
    if (!root) {
        fprintf(out, "N\n");
        return;
    }

    fprintf(out, "S %s %d\n", root->val.val, root->frequency);
    save_tree_nodes(root->left, out);
    save_tree_nodes(root->right, out);
}

int load_tree_from_file(const char *filepath, Node **result) {
    FILE *file = fopen(filepath, "r");
    if (!file)
        return throw_err(FILE_ERROR);

    Node *root = NULL;
    load_tree_nodes(&root, file);

    fclose(file);

    if (*result) {
        destroy_tree(*result);
    }

    *result = root;

    return 0;
}

int load_tree_nodes(Node **root, FILE *file) {
    char type;

    int err;

    String val;
    Array temp;

    err = create_arr(5, &temp);
    if (err)
        return err;

    int frequency;

    if (fscanf(file, " %c", &type) != 1) {
        destroy(&temp);
        return 0;
    }

    if (type == 'S') {
        fgetc(file);

        err = read_value(&file, &temp, 0);
        if (err) {
            destroy(&temp);
            return err;
        }

        err = create_str(&val, temp.val);
        if (err) {
            destroy(&temp);
            return err;
        }

        err = fscanf(file, "%d", &frequency);
        if (!err) {
            destroy_str(&val);
            destroy(&temp);
            return throw_err(INCORRECT_INPUT_DATA);
        }

        *root = create_tree_node(val);
        if (!(*root)) {
            destroy_str(&val);
            destroy(&temp);
            return throw_err(MEMORY_NOT_ALLOCATED);
        }

        (*root)->frequency = frequency;
        err = load_tree_nodes(&(*root)->left, file);
        if (err) {
            destroy_str(&val);
            destroy(&temp);
            return err;
        }

        err = load_tree_nodes(&(*root)->right, file);
        if (err) {
            destroy_str(&val);
            destroy(&temp);
            return err;
        }

        reset(&temp);
        destroy_str(&val);
    }

    destroy(&temp);

    return 0;
}