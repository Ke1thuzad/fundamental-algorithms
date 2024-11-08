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

        return 0;
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
    if (!root) {
        printf("%*s\n", level * 10, "N");
        return;
    }

    print_tree(root->left, level + 1);

    printf("%*s\n", level * 10, root->val.val);

    print_tree(root->right, level + 1);
}

int tree_depth(Node *root, int *max_depth) {
    if (!root) {
        *max_depth = 0;
        return 0;
    }

    tree_depth(root->left, max_depth);
    (*max_depth)++;
    tree_depth(root->right, max_depth);
    (*max_depth)++;

    return 0;
}

int find_most_frequent_words(Node *root, NodeList **most_frequent) {
    if (!root)
        return 0;

    find_most_frequent_words(root->left, most_frequent);

    int err = insert_list_condition(most_frequent, root, compare_frequency);
    if (err)
        return err;

    find_most_frequent_words(root->right, most_frequent);
}

int search_word(Node *root, String val, Node **result) {
    if (!root)
        return throw_err(INCORRECT_ARGUMENTS);

    Node *cur = root;

    while (1) {
        if (!cur)
            return 1;

        int cmp = compare_str(val, cur->val);
        if (cmp > 0) {
            cur = cur->right;
        } else if (cmp < 0) {
            cur = cur->left;
        } else {
            *result = cur;
            return 0;
        }
    }
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

    root = NULL;
}
