#ifndef FUNDAMENTAL_ALGORITHMS_HASHSET_H
#define FUNDAMENTAL_ALGORITHMS_HASHSET_H

#define HASHSIZE 128

#include "../department.h"

#include <limits.h>

typedef struct Node {
    Department *department;
    unsigned long hash;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node **table;
    unsigned long size;
} HashTable;


int create_node(Node *node, Department *department);
void destroy_node(Node *node);

int insert_node(HashTable *table, Department *department);
int insert_node_hash(HashTable *table, Department *department, unsigned long hash);
int create_hash_table(HashTable *table, unsigned long size);

int get_from_hashtable(HashTable *ht, String def_name, Department **def_department);
void destroy_hash_table(HashTable *table);
int rehash(HashTable *ht, unsigned long new_size);
int check_and_rehash(HashTable *ht);

int base_char_to_value(char c);
int hash_function(String str, unsigned long *hash, unsigned long hash_size);

#endif //FUNDAMENTAL_ALGORITHMS_HASHSET_H
