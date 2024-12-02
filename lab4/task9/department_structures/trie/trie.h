#pragma once

#ifndef FUNDAMENTAL_ALGORITHMS_TRIE_H
#define FUNDAMENTAL_ALGORITHMS_TRIE_H

#include "../department.h"

typedef struct TrieNode {
    char character;
    Department *department;
    unsigned char terminating;
    struct TrieNode *parent;
    struct TrieNode *sibling;
    struct TrieNode *child;
} TrieNode;

TrieNode *create_trie_node(char c);

int insert_department_trie_node(TrieNode *root, Department *department);

Department* search_department_trie(TrieNode *root, Department department);

int find_least_loaded_department_trie(TrieNode *root, Department **result);

void destroy_trie(TrieNode *root);


#endif //FUNDAMENTAL_ALGORITHMS_TRIE_H
