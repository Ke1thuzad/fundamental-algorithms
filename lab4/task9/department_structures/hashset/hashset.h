#ifndef FUNDAMENTAL_ALGORITHMS_HASHSET_H
#define FUNDAMENTAL_ALGORITHMS_HASHSET_H

#define HASHSIZE 128

#include "../department.h"

#include <limits.h>

typedef struct HashNode {
    Department *department;
    unsigned long hash;
    struct HashNode *next;
} HashNode;

typedef struct HashTable {
    HashNode **table;
    unsigned long size;
} HashTable;

int create_hashnode(HashNode *node, Department *department);

void destroy_hashnode(HashNode *node);

int create_hash_table(HashTable *table, unsigned long size);

HashTable *create_standard_hash_table();

int insert_hashnode(HashTable *table, Department *department);

int insert_hashnode_hash(HashTable *table, Department *department, unsigned long hash);

int get_from_hashtable(HashTable *ht, String def_name, Department **def_department);

int rehash(HashTable *ht, unsigned long new_size);

void destroy_hash_table(HashTable *table);

int check_and_rehash(HashTable *ht);

int base_char_to_value(char c);

int hash_function(String str, unsigned long *hash, unsigned long hash_size);

#endif //FUNDAMENTAL_ALGORITHMS_HASHSET_H
