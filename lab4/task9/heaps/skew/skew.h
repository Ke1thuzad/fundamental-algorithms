#ifndef FUNDAMENTAL_ALGORITHMS_SKEW_H
#define FUNDAMENTAL_ALGORITHMS_SKEW_H

#include "../../ticket.h"

typedef struct SkewNode {
    Ticket ticket;
    struct SkewNode *left;
    struct SkewNode *right;
} SkewNode;

typedef struct SkewHeap {
    SkewNode *head;
    size_t size;
} SkewHeap;

SkewNode *create_skew_node(Ticket ticket);
void swap_nodes_skew(SkewNode **node1, SkewNode **node2);
void destroy_skew_nodes(SkewNode *root);
SkewNode *merge_skew_heap(SkewNode *head1, SkewNode *head2);

SkewHeap *create_skew_heap();
int insert_skew_heap(SkewHeap *heap, Ticket ticket);

int extract_max_skew_heap(SkewHeap *heap, Ticket *result);
Ticket get_max_skew_heap(SkewHeap *heap);

void destroy_skew_heap(SkewHeap *heap);

SkewNode* copy_skew_node(SkewNode* node);
SkewHeap* copy_skew_heap(SkewHeap* heap);
int merge_skew_heap_with_copy(SkewHeap *heap1, SkewHeap *heap2, SkewHeap *result);

#endif //FUNDAMENTAL_ALGORITHMS_SKEW_H
