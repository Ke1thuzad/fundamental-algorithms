#ifndef FUNDAMENTAL_ALGORITHMS_TREAP_H
#define FUNDAMENTAL_ALGORITHMS_TREAP_H

#include "../../ticket.h"

typedef struct TreapNode {
    Ticket ticket;
    struct TreapNode *left;
    struct TreapNode *right;
} TreapNode;

typedef struct Treap {
    TreapNode *head;
    int size;
} Treap;

TreapNode *create_treap_node(Ticket ticket);
Treap *create_treap();

int split_treap(TreapNode *head, String key, TreapNode **result1, TreapNode** result2);
TreapNode *merge_treap(TreapNode *a, TreapNode *b);

int insert_treap(Treap *head, Ticket ticket);
int extract_max_treap(Treap *head, Ticket *res);
Ticket get_max_treap(Treap *head);

TreapNode *copy_treap_node(TreapNode *node);
Treap *copy_treap(Treap *original);
int merge_treap_with_copy(Treap *treap1, Treap *treap2, Treap *result);

void destroy_treap_node(TreapNode *node);
void destroy_treap(Treap *treap);


#endif //FUNDAMENTAL_ALGORITHMS_TREAP_H
