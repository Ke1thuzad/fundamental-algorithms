#include "main.h"

Node *create_tree_node(String val) {
    Node *res = (Node *) malloc(sizeof(Node));
    if (!res)
        return NULL;

    copy_newstr(&res->val, &val);

    res->frequency = 1;

    res->left = NULL;
    res->right = NULL;

    return res;
}

int insert_tree(Node **root, String val) {
    if (*root == NULL) {
        *root = create_tree_node(val);
        if (!*root)
            return throw_err(MEMORY_NOT_ALLOCATED);

        return 1;
    }

    Node *current = *root;
    while (1) {
        int cmp = compare_str(val, current->val);
        if (cmp < 0) {
            if (current->left == NULL) {
                current->left = create_tree_node(val);
                if (!current->left)
                    return throw_err(MEMORY_NOT_ALLOCATED);

                return 0;
            }
            current = current->left;
        } else if (cmp > 0) {
            if (current->right == NULL) {
                current->right = create_tree_node(val);
                if (!current->right)
                    return throw_err(MEMORY_NOT_ALLOCATED);

                return 0;
            }
            current = current->right;
        } else {
            current->frequency++;
            return 0;
        }
    }
}

void print_tree(Node *root, int level) {
    if (!root)
        return;

    print_tree(root->left, level + 1);

    printf("%*s\n", level * 5, root->val.val);

    print_tree(root->right, level + 1);
}

int depth(Node *root, int *max_depth) {
    if (!root) {
        *max_depth = 0;
        return 0;
    }

    depth(root->left, max_depth);
    (*max_depth)++;
    depth(root->right, max_depth);
    (*max_depth)++;

    return 0;
}

void find_most_frequent_words(Node *root, NodeList **most_frequent, int *max_frequency) {
    if (!root)
        return;

    find_most_frequent_words(root->left, most_frequent, max_frequency);

    insert_list_condition(most_frequent, root, compare_frequency);
//    if (root->frequency > *max_frequency) {
//        *max_frequency = root->frequency;
////        *most_frequent = root;
//    }

    find_most_frequent_words(root->right, most_frequent, max_frequency);
}

void destroy_tree_nodes(Node *root) {
    if (!root)
        return;

    destroy_str(&root->val);

    if (root->left) {
        destroy_tree_nodes(root->left);
        free(root->left);
        root->left = NULL;
    }

    if (root->right) {
        destroy_tree_nodes(root->right);
        free(root->right);
        root->right = NULL;
    }
}

void destroy_tree(Node *root) {
    destroy_tree_nodes(root);

    free(root);
}
