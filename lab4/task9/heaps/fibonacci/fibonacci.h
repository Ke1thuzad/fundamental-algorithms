#ifndef FUNDAMENTAL_ALGORITHMS_FIBONACCI_H
#define FUNDAMENTAL_ALGORITHMS_FIBONACCI_H

#include "../../ticket.h"

#include <math.h>

typedef struct FibonacciNode {
    Ticket ticket;
    int degree;
    unsigned char marked;
    struct FibonacciNode *parent;
    struct FibonacciNode *left;
    struct FibonacciNode *right;
    struct FibonacciNode *child;
} FibonacciNode;

typedef struct FibonacciHeap {
    int size;
    FibonacciNode *max;
} FibonacciHeap;

FibonacciNode *create_fibonacci_node(Ticket ticket);
FibonacciHeap *create_fibonacci_heap();

int insert_fibonacci_heap(FibonacciHeap *heap, Ticket ticket);

int get_max_degree_fibonacci_heap(FibonacciHeap *heap);
void union_fibonacci_roots(FibonacciNode *heap1, FibonacciNode *heap2);
int merge_fibonacci_heap(FibonacciHeap **heap1, FibonacciHeap *heap2);

void link_fibonacci_nodes(FibonacciNode *child, FibonacciNode *parent);
void consolidate_fibonacci_heap(FibonacciHeap *heap);

Ticket get_max_fibonacci_heap(FibonacciHeap *heap);
int extract_max_fibonacci_heap(FibonacciHeap *heap, Ticket *result);
void destroy_fibonacci_heap(FibonacciHeap *heap);

FibonacciHeap* copy_fibonacci_heap(FibonacciHeap* heap);
int merge_fibonacci_heap_with_copy(FibonacciHeap *heap1, FibonacciHeap *heap2, FibonacciHeap *result);

void print_fibonacci_node(FibonacciNode* node, int level);

void print_fibonacci_heap(FibonacciHeap* heap);

size_t get_size_fibonacci_heap(FibonacciHeap *heap);

#endif //FUNDAMENTAL_ALGORITHMS_FIBONACCI_H
