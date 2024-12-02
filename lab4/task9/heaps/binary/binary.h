#ifndef FUNDAMENTAL_ALGORITHMS_BINARY_H
#define FUNDAMENTAL_ALGORITHMS_BINARY_H

#include "../../ticket.h"

#include <math.h>
#include <stddef.h>
#include <string.h>

typedef struct BinaryNode {
    Ticket ticket;
} BinaryNode;

typedef struct BinaryHeap {
    BinaryNode *heap;
    size_t size;
    size_t capacity;
} BinaryHeap;

BinaryHeap *create_binary_heap();
int resize_binary_heap(BinaryHeap *heap);

void swap_binary_nodes(BinaryNode *a, BinaryNode *b);
void sift_down_binary_heap(BinaryHeap *heap, int index);
void sift_up_binary_heap(BinaryHeap *heap, int index);

int insert_binary_heap(BinaryHeap *heap, Ticket ticket);
int extract_max_binary_heap(BinaryHeap *heap, Ticket *res);
Ticket get_max_binary_heap(BinaryHeap *heap);

void destroy_binary_heap(BinaryHeap *heap);

void print_binary_heap_as_tree(BinaryHeap *heap);

#endif //FUNDAMENTAL_ALGORITHMS_BINARY_H
