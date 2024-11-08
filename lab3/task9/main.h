#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include "../../utility/error_handler.h"
#include "../../utility/arrays/array.h"
#include "../../utility/overio.h"
#include "../task4/mystring.h"

typedef struct Node {
    String val;
    int frequency;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct NodeList {
    Node *val;
    struct NodeList *next;
} NodeList;

typedef enum Command {
    HELP,
    PRINT,
    SEARCH,
    N_MOST_FREQUENT,
    EDGES,
    DEPTH,
    SAVE,
    LOAD
} Command;

typedef enum DialogFSM {
    COMMAND_WAIT,
    COMMAND_HANDLE
} DialogFSM;


// BSTree
Node *create_tree_node(String val);
int insert_tree(Node **root, String val);
void print_tree(Node *root, int level);
int tree_depth(Node *root, int *max_depth);
int find_most_frequent_words(Node *root, NodeList **most_frequent);
int search_word(Node *root, String val, Node **result);
void destroy_tree_nodes(Node *root);
void destroy_tree(Node *root);

// Linked List
NodeList* create_node(Node *val);
int prepend_list(NodeList **list, Node *val);
int append_list(NodeList **list, Node *val);
int insert_list_condition(NodeList **list, Node *val, int (*cmp)(const void*, const void*));
int compare_frequency(const void *a, const void *b);
void print_list(FILE *out, NodeList *list);
void destroy_list(NodeList **list);

// Dialog
int dialog_manager(FILE *in, char **argv, int argc);
int parse_file_seps(FILE *in, Node **root, char **argv, int argc);
int wait_command(Command *result);
int handle_command(Command cmd, Node **root);
int wait_param(Command cmd, int *param);
int read_whole_input_str(String *result);
void cmd_description(Command cmd);
void help_cmd();
Node *find_longest_word(Node *root);
Node *find_shortest_word(Node *root);
int save_tree_to_file(Node *root, const char *filepath);
void save_tree_nodes(Node *root, FILE *out);
int load_tree_from_file(const char *filepath, Node **result);
int load_tree_nodes(Node **root, FILE *file);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
