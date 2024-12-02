#ifndef FUNDAMENTAL_ALGORITHMS_BST_H
#define FUNDAMENTAL_ALGORITHMS_BST_H

#include "../department.h"

typedef struct BSTNode {
    Department *department;

    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

BSTNode *create_department_bstree_node(Department *department) {
    BSTNode *node = (BSTNode*) calloc(1, sizeof(BSTNode));
    if (!node)
        return NULL;

    node->department = department;  // TODO: change pointer?

//    copy_newstr(&node->department->id, &department.id); TODO: copy ?

    node->left = NULL;
    node->right = NULL;

    return node;
}

int insert_department_bstree(BSTNode **root, Department *department) {
    if (*root == NULL) {
        *root = create_department_bstree_node(department);
        if (!*root)
            return throw_err(MEMORY_NOT_ALLOCATED);
    }

    BSTNode *current = *root;
    while (1) {
        int cmp = compare_str(department->id, current->department->id);
        if (cmp <= 0) {
            if (current->left == NULL) {
                current->left = create_department_bstree_node(department);
                if (!current->left)
                    return throw_err(MEMORY_NOT_ALLOCATED);

                return 0;
            }
            current = current->left;
        }
        else {
            if (current->right == NULL) {
                current->right = create_department_bstree_node(department);
                if (!current->right)
                    return throw_err(MEMORY_NOT_ALLOCATED);

                return 0;
            }
            current = current->right;
        }
    }
}

void traverse_department_bst(BSTNode *node, float *min_load, Department **min_department) {
    float eps = 0.00001f;

    if (!node)
        return;

    float current_load = get_department_load(*node->department);
    if (current_load - *min_load < eps) {
        *min_load = current_load;
        *min_department = node->department;
    }

    traverse_department_bst(node->left, min_load, min_department);
    traverse_department_bst(node->right, min_load, min_department);
}

Department* find_least_overloaded_department(BSTNode *root) {
    if (!root)
        return NULL;

    Department *min_department = root->department;
    float min_load = get_department_load(*root->department);

    traverse_department_bst(root, &min_load, &min_department);

    return min_department;
}


void destroy_department_bstree_nodes(BSTNode *root) {
    if (!root)
        return;

    destroy_department(root->department);

    if (root->left) {
        destroy_department_bstree_nodes(root->left);
        root->left = NULL;
    }

    if (root->right) {
        destroy_department_bstree_nodes(root->right);
        root->right = NULL;
    }

    free(root);
}

void destroy_department_bstree(BSTNode *root) {
    destroy_department_bstree_nodes(root);

    free(root);
}




#endif //FUNDAMENTAL_ALGORITHMS_BST_H
