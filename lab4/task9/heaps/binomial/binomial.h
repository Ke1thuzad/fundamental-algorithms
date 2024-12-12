#ifndef FUNDAMENTAL_ALGORITHMS_BINOMIAL_H
#define FUNDAMENTAL_ALGORITHMS_BINOMIAL_H

#include "../../ticket.h"

typedef struct BinomialNode {
    Ticket ticket;
    int degree;
    struct BinomialNode *parent;
    struct BinomialNode *sibling;
    struct BinomialNode *child;
} BinomialNode;

typedef struct BinomialHeap {
    BinomialNode *head;
    size_t size;
} BinomialHeap;

BinomialHeap* create_binomial_heap();
BinomialNode* create_binomial_node(Ticket ticket);
BinomialNode* copy_binomial_node(BinomialNode* node);
BinomialNode *search_key_binomial_tree(BinomialNode *root, String key);
BinomialHeap* copy_binomial_heap(BinomialHeap* heap);

BinomialNode *simple_merge_binomial_heap(BinomialNode *head1, BinomialNode *head2);
BinomialNode *merge_binomial_heap(BinomialNode *head1, BinomialNode *head2);
int merge_binomial_heap_with_copy(BinomialHeap *heap1, BinomialHeap *heap2, BinomialHeap *result);

int insert_binomial_heap(BinomialHeap *heap, Ticket ticket);
int test_binomial_heap(BinomialNode *heap);
void destroy_binomial_heap(BinomialHeap* heap);
void destroy_binomial_node(BinomialNode* node);

int count_nodes_binomial_heap(BinomialNode *head);
int extract_max_binomial_heap(BinomialHeap *heap, Ticket *result);
Ticket get_max_priority_binomial_heap(BinomialHeap *heap);

void print_binomial_tree(BinomialNode *node, int level);
void print_binomial_heap(BinomialNode *head);

size_t get_size_binomial_heap(BinomialHeap *heap);

#endif //FUNDAMENTAL_ALGORITHMS_BINOMIAL_H
