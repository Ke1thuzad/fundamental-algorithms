#ifndef FUNDAMENTAL_ALGORITHMS_LEFTIST_H
#define FUNDAMENTAL_ALGORITHMS_LEFTIST_H

#include "../../ticket.h"

typedef struct LeftistNode {
    Ticket ticket;
    int NPL;
    struct LeftistNode* left;
    struct LeftistNode* right;
} LeftistNode;

typedef struct LeftistHeap {
    LeftistNode *head;
    size_t size;
} LeftistHeap;

LeftistNode *create_leftist_node(Ticket ticket);
void swap_nodes_leftist(LeftistNode **node1, LeftistNode **node2);
void destroy_leftist_nodes(LeftistNode *root);

LeftistHeap *create_leftist_heap();
int insert_leftist_heap(LeftistHeap *heap, Ticket ticket);
void destroy_leftist_heap(LeftistHeap *heap);

int extract_max_leftist_heap(LeftistHeap *heap, Ticket *result);
Ticket get_max_leftist_heap(LeftistHeap *heap);

LeftistNode* merge_leftist_heap(LeftistNode *head1, LeftistNode *head2);
LeftistNode* copy_leftist_node(LeftistNode* node);
LeftistHeap* copy_leftist_heap(LeftistHeap* heap);
int merge_leftist_heap_with_copy(LeftistHeap *heap1, LeftistHeap *heap2, LeftistHeap *result);

size_t get_size_leftist_heap(LeftistHeap *heap);

#endif //FUNDAMENTAL_ALGORITHMS_LEFTIST_H
