#pragma once

#ifndef FUNDAMENTAL_ALGORITHMS_DEPARTMENT_H
#define FUNDAMENTAL_ALGORITHMS_DEPARTMENT_H

#include "department_structure.h"

#include "bst/bst.h"
#include "dynamic_array/dynamic_array.h"
#include "hashset/hashset.h"
#include "trie/trie.h"
#include "overload_heap/overload_heap.h"

#include <time.h>

typedef struct BSTDept BSTDept;
typedef struct DepartmentArray DepartmentArray;
typedef struct HashTable HashTable;
typedef struct TrieNode TrieNode;

typedef enum StorageType {
    BST,
    DYNAMIC_ARRAY,
    HASHSET,
    TRIE
} StorageType;

typedef union D_storage {
    BSTDept *bst;
    DepartmentArray *dept_array;
    HashTable *hashset;
    TrieNode *trie;
} D_storage;

typedef struct dept_functions {
    D_storage *(*create)();
    int (*insert)(D_storage *storage, Department *department);
    int (*get)(D_storage *storage, String id, Department **result);
    void (*destroy)(D_storage *storage);
} dept_functions;

extern const dept_functions STORAGE_IMPLEMENTATIONS[];

char *generate_base52_string(int len);

String *randomize_operator_name(Department *department);

int is_operator_name_unique(Department *department, char *name);

float get_department_load(Department department);

void destroy_department(Department *department);

#endif //FUNDAMENTAL_ALGORITHMS_DEPARTMENT_H
