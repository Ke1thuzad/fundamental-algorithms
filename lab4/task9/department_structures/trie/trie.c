#include "trie.h"

TrieNode *create_trie() {
    TrieNode *trie = (TrieNode*) calloc(1, sizeof(TrieNode));
    if (!trie)
        return NULL;

    return trie;
}

TrieNode *create_trie_node(char c) {
    TrieNode *new_node = (TrieNode*) calloc(1, sizeof(TrieNode));
    if (!new_node)
        return NULL;

    new_node->character = c;

    return new_node;
}

int insert_department_trie_node(TrieNode *root, Department *department) {
    TrieNode *cur = root;

    for (int i = 0; i < department->id.length; ++i) {
        int found = 0;
        if (!cur->child) {
            cur->child = create_trie_node(department->id.val[i]);
            if (!cur->child)
                return throw_err(MEMORY_NOT_ALLOCATED);

            cur->child->parent = cur;
            cur = cur->child;
            found = 1;
        } else {
            TrieNode *next_sibling = cur->child;
            TrieNode *prev = NULL;

            while (next_sibling) {
                if (next_sibling->character == department->id.val[i]) {
                    found = 1;
                    cur = next_sibling;
                    break;
                }
                prev = next_sibling;
                next_sibling = next_sibling->sibling;
            }

            if (!found) {
                TrieNode *new_node = create_trie_node(department->id.val[i]);
                if (!new_node)
                    return throw_err(MEMORY_NOT_ALLOCATED);

                new_node->parent = cur;
                if (prev)
                    prev->sibling = new_node;
                else
                    cur->child = new_node;

                cur = new_node;
            }
        }

        if (i == department->id.length - 1) {
            cur->terminating = 1;
            cur->department = department;
        }
    }

    return 0;
}

int search_department_trie(TrieNode *root, String id, Department **result) {
    TrieNode *cur = root;

    for (int i = 0; i < id.length; i++) {
        TrieNode *next = cur->child;
        int found = 0;

        while (next) {
            if (next->character == id.val[i]) {
                found = 1;
                cur = next;
                break;
            }
            next = next->sibling;
        }

        if (!found)
            return 0;
    }

    if (cur->terminating) {
        *result = cur->department;
        return 1;
    }

    *result = NULL;

    return 0;
}

//int find_least_loaded_department_trie(TrieNode *root, Department **result) {
//    if (!root || !result)
//        return -1;
//
//    static float min_load = 10000;
//    static Department *min_department = NULL;
//
//    if (root->terminating) {
//        float current_load = get_department_load(*root->department);
//        if (current_load < min_load) {
//            min_load = current_load;
//            min_department = root->department;
//        }
//    }
//
//    TrieNode *child = root->child;
//    while (child) {
//        find_least_loaded_department_trie(child, result);
//        child = child->sibling;
//    }
//
//    *result = min_department;
//    return 0;
//}


void destroy_trie(TrieNode *root) {
    if (!root)
        return;

    TrieNode *child = root->child;
    while (child) {
        TrieNode *next = child->sibling;
        destroy_trie(child);
        child = next;
    }

    if (root->terminating) {
        destroy_department(root->department);
        free(root->department);
        root->department = NULL;
    }

    free(root);
}
