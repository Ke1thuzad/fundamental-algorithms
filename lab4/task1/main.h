#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include "../../utility/error_handler.h"
#include "../../utility/arrays/array.h"
#include "../../lab3/task4/mystring.h"

#include <string.h>

#define HASHSIZE 128

#include <limits.h>

typedef struct Node {
    String def_name;
    String value;
    unsigned long hash;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node **table;
    unsigned long size;
} HashTable;


int create_node(Node *node, String def_name, String value);
void destroy_node(Node *node);

int insert_node(HashTable *table, String def_name, String value);
int insert_node_hash(HashTable *table, String def_name, String value, unsigned long hash);
int create_hash_table(HashTable *table, unsigned long size);
void print_hash_table(HashTable *ht);
void destroy_hash_table(HashTable *table);
void rehash(HashTable *ht, unsigned long new_size);
void check_and_rehash(HashTable *ht);

int base_char_to_value(char c);
int hash_function(String str, unsigned long *hash, unsigned long hash_size);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
