#ifndef FUNDAMENTAL_ALGORITHMS_BST_H
#define FUNDAMENTAL_ALGORITHMS_BST_H

#include "../department.h"

typedef struct BSTNode {
    Department *department;

    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

typedef struct BSTDept {
    BSTNode *root;
    int size;
} BSTDept;

BSTDept *create_department_bst();

BSTNode *create_department_bstree_node(Department *department);

int insert_department_bstree(BSTDept *head, Department *department);

int get_from_department_bstree(BSTDept *head, String id, Department **res);

void destroy_department_bstree_nodes(BSTNode *root);

void destroy_department_bstree(BSTDept *head);




#endif //FUNDAMENTAL_ALGORITHMS_BST_H
