#include "bst.h"

BSTDept *create_department_bst() {
    BSTDept *res = (BSTDept*) calloc(1, sizeof(BSTDept));
    if (!res)
        return NULL;

    return res;
}

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

int insert_department_bstree(BSTDept *head, Department *department) {
    if (!head || !department)
        return throw_err(INCORRECT_ARGUMENTS);

    if (head->root == NULL) {
        head->root = create_department_bstree_node(department);
        if (!head->root)
            return throw_err(MEMORY_NOT_ALLOCATED);

        return 0;
    }

    BSTNode *current = head->root;

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

void destroy_department_bstree_nodes(BSTNode *root) {
    if (!root)
        return;

    destroy_department(root->department);
    free(root->department);
    root->department = NULL;

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

void destroy_department_bstree(BSTDept *head) {
    destroy_department_bstree_nodes(head->root);
    head->root = NULL;
    head->size = 0;

    free(head);
}

int get_from_department_bstree(BSTDept *head, String id, Department **res) {
    if (!head)
        return throw_err(INCORRECT_ARGUMENTS);

    BSTNode *cur = head->root;

    while (cur) {
        if (compare_str(id, cur->department->id) > 0) {
            cur = cur->right;
        } else if (compare_str(id, cur->department->id) < 0) {
            cur = cur->left;
        } else {
            *res = cur->department;

            return 1;
        }
    }

    return 0;
}
