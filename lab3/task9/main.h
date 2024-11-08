#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include "../../utility/error_handler.h"
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

Node *create_tree_node(String val);
int insert_tree(Node **root, String val);
void print_tree(Node *root, int level);
int depth(Node *root, int *max_depth);
void find_most_frequent_words(Node *root, NodeList **most_frequent, int *max_frequency);
void destroy_tree_nodes(Node *root);
void destroy_tree(Node *root);

NodeList* create_node(Node *val);
int prepend_list(NodeList **list, Node *val);
int append_list(NodeList **list, Node *val);
int insert_list_condition(NodeList **list, Node *val, int (*cmp)(const void*, const void*));
int compare_frequency(const void *a, const void *b);
void print_list(FILE *out, NodeList *list);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
