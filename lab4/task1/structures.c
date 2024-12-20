#include "main.h"

int create_node(Node *node, String def_name, String value) {
    int err = copy_newstr(&node->def_name, &def_name);
    if (err)
        return err;

    err = copy_newstr(&node->value, &value);
    if (err)
        return err;

    node->next = NULL;

    return 0;
}

void destroy_node(Node *node) {
    destroy_str(&node->def_name);
    destroy_str(&node->value);

    if (node->next) {
        destroy_node(node->next);
        free(node->next);
        node->next = NULL;
    }
}

int insert_node(HashTable *table, String def_name, String value) {
    int res =  insert_node_hash(table, def_name, value, table->size);

    int err = check_and_rehash(table);
    if (err)
        return err;

    return res;
}

int insert_node_hash(HashTable *table, String def_name, String value, unsigned long hash) {
    int err;
    unsigned long hash_new = hash;

    if (hash == table->size) {
        err = hash_function(def_name, &hash_new, table->size);
        if (err)
            return err;
    }

    Node *node = (Node*) calloc(1, sizeof(Node));
    if (!node)
        return throw_err(MEMORY_NOT_ALLOCATED);

    err = create_node(node, def_name, value);
    if (err)
        return err;

    node->hash = hash_new;

    hash_new %= table->size;

    if (!table->table[hash_new]) {
        table->table[hash_new] = node;
    } else {
        node->next = table->table[hash_new];
        table->table[hash_new] = node;
    }

    return 0;
}

int create_hash_table(HashTable *table, unsigned long size) {
    table->table = (Node**) calloc(size, sizeof(Node *));
    if (!table->table)
        return throw_err(MEMORY_NOT_ALLOCATED);

    table->size = size;

    return 0;
}

void print_hash_table(HashTable *ht) {
    for (int i = 0; i < ht->size; i++) {
        Node *current = ht->table[i];
        while (current != NULL) {
            printf("(%s, %s, %lu) ", current->def_name.val, current->value.val, current->hash % ht->size);
            current = current->next;
        }
    }
}

int get_from_hashtable(HashTable *ht, String def_name, String *def_value) {
    if (!ht)
        return throw_err(INCORRECT_ARGUMENTS);

    int err;

    unsigned long hash;

    err = hash_function(def_name, &hash, ht->size);
    if (err)
        return err;

    hash %= ht->size;

    Node *val = ht->table[hash], *prev = val;

    int i = 0;

    if (val) {
        while (val && i < ht->size - 1) {
            prev = val;
            err = hash_function(val->value, &hash, ht->size);
            if (err)
                return err;

            hash %= ht->size;
            val = ht->table[hash];
            if (val && !equiv_str(val->def_name, prev->value)) {
                break;
            }

            i++;
            if (val)
                def_name = val->def_name;
        }

        if (equiv_str(prev->def_name, def_name))
            *def_value = prev->value;
        else {
            while (prev) {
                if (equiv_str(prev->def_name, def_name)) {
                    *def_value = prev->value;
                    return 0;
                }

                prev = prev->next;
            }

            return 1;
        }


    } else {
        return 1;
    }

    return 0;
}

int rehash(HashTable *ht, unsigned long new_size) {
    HashTable *new_ht = (HashTable *) malloc(sizeof(HashTable));
    if (!new_ht)
        return throw_err(MEMORY_NOT_ALLOCATED);

    int err = create_hash_table(new_ht, new_size);
    if (err)
        return err;

    for (int i = 0; i < ht->size; i++) {
        Node *current = ht->table[i];
        while (current != NULL) {
            if (new_ht->size >= current->hash)
                insert_node_hash(new_ht, current->def_name, current->value, new_ht->size);
            else
                insert_node_hash(new_ht, current->def_name, current->value, current->hash);

            current = current->next;
        }
    }

    destroy_hash_table(ht);

    ht->table = new_ht->table;
    ht->size = new_ht->size;
    free(new_ht);

    return 0;
}

int check_and_rehash(HashTable *ht) {
    unsigned long min_chain_length = ht->size;
    unsigned long max_chain_length = 0;

    for (int i = 0; i < ht->size; i++) {
        int chain_length = 0;
        Node *current = ht->table[i];
        while (current != NULL) {
            chain_length++;
            current = current->next;
        }
        if (chain_length > 1 && chain_length < min_chain_length)
            min_chain_length = chain_length;

        if (chain_length > max_chain_length)
            max_chain_length = chain_length;
    }

    if (min_chain_length != ht->size && max_chain_length > 2 * min_chain_length) {
        unsigned long new_size = ht->size * 2;
        int err = rehash(ht, new_size);
        if (err)
            return err;
    }

    return 0;
}

void destroy_hash_table(HashTable *table) {
    for (int i = 0; i < table->size; ++i) {
        if (table->table[i]) {
            destroy_node(table->table[i]);
            free(table->table[i]);
            table->table[i] = NULL;
        }
    }

    free(table->table);
}

int base_char_to_value(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';

    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 10;

    if (c >= 'a' && c <= 'z')
        return c - 'a' + 36;

    return -1;
}

int hash_function(String str, unsigned long *hash, unsigned long hash_size) {
    int i = 0;
    hash_size = 100000;

    *hash = base_char_to_value(str.val[i++]);
    int base = 62;

    for (; i < str.length; ++i) {
        int char_value = base_char_to_value(str.val[i]);
        if (char_value == -1)
            continue;

        unsigned long a = (*hash * base + char_value);

//        printf("| %llu | %llu | %lu |\n", a % HASHSIZE, a % (HASHSIZE * 2), a);
        if (i < str.length - 1)
            *hash = a % hash_size;
        else
            *hash = a;
    }

    return 0;
}


