#include "main.h"

NodeList* create_node(Node *val) {
    NodeList *new = (NodeList*) malloc(sizeof(NodeList));
    if (!new)
        return NULL;

    new->next = NULL;

    new->val = val;

    return new;
}

int prepend_list(NodeList **list, Node *val) {
    NodeList *new = create_node(val);
    if (!new)
        return throw_err(MEMORY_NOT_ALLOCATED);

    new->next = *list;

    *list = new;

    return 0;
}

int append_list(NodeList **list, Node *val) {

    NodeList *new = create_node(val);
    if (!new)
        return throw_err(MEMORY_NOT_ALLOCATED);

    if (*list == NULL) {
        *list = new;
        return 0;
    }

    NodeList *temp = *list;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = new;

    return 0;
}

int insert_list_condition(NodeList **list, Node *val, int (*cmp)(const void*, const void*)) {
    NodeList *cur = *list, *prev = cur;
    int err;

    while (cur) {

        if (cmp(cur->val, val) >= 0) {
            if (cur == *list) {
                err = prepend_list(list, val);

                if (err)
                    return err;

                return 0;
            }

            NodeList *new_node = create_node(val);
            if (!new_node)
                return throw_err(MEMORY_NOT_ALLOCATED);

            new_node->next = cur;
            prev->next = new_node;

            return 0;
        }

        prev = cur;
        cur = cur->next;
    }

    err = append_list(list, val);
    if (err)
        return err;

    return 0;
}

void destroy_list(NodeList **list) {
    NodeList *cur = *list, *prev;

    while (cur) {
        prev = cur;
        cur = cur->next;

        free(prev);
    }

    *list = NULL;
}

int compare_frequency(const void *a, const void *b) {
    Node *node1 = (Node *)a;
    Node *node2 = (Node *)b;

    return node2->frequency - node1->frequency;
}

void print_list(FILE *out, NodeList *list) {
    NodeList *cur = list;

    while (cur) {
        fprintf(out, "\tNode %s with frequency %d.\n", cur->val->val.val, cur->val->frequency);
        fprintf(out, "\n");

        cur = cur->next;
    }

    fprintf(out, "\n");
}