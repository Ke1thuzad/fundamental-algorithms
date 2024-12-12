#ifndef FUNDAMENTAL_ALGORITHMS_OVERLOAD_HEAP_H
#define FUNDAMENTAL_ALGORITHMS_OVERLOAD_HEAP_H

#include "../department.h"
#include <string.h>

typedef struct OverloadNode {
    String id;
    float overload;
} OverloadNode;

typedef struct OverloadBinaryHeap {
    OverloadNode *heap;
    size_t size;
    size_t capacity;
} OverloadBinaryHeap;

OverloadBinaryHeap *create_overload_binary_heap();

int resize_overload_binary_heap(OverloadBinaryHeap *heap);

void swap_overload_binary_nodes(OverloadNode *a, OverloadNode *b);

void sift_down_overload_binary_heap(OverloadBinaryHeap *heap, int index);

void sift_up_overload_binary_heap(OverloadBinaryHeap *heap, int index);

int insert_overload_binary_heap(OverloadBinaryHeap *heap, Department department);

int extract_min_overload_binary_heap(OverloadBinaryHeap *heap, String *id);

String get_min_overload_binary_heap(OverloadBinaryHeap *heap);

void destroy_overload_binary_heap(OverloadBinaryHeap *heap);

OverloadBinaryHeap *copy_overload_binary_heap(const OverloadBinaryHeap *heap);

int change_key_overload_binary_heap(OverloadBinaryHeap *heap, String id, float new_overload);

//OverloadBinaryHeap *merge_overload_binary_heap_with_copy(const OverloadBinaryHeap *heap1, const OverloadBinaryHeap *heap2) {
//    OverloadBinaryHeap *copy1 = copy_overload_binary_heap(heap1);
//
//    if (!copy1)
//        return NULL;
//
//    for (size_t i = 0; i < heap2->size; i++) {
//        if (insert_overload_binary_heap(copy1, heap2->heap[i].) != 0) {
//            destroy_overload_binary_heap(copy1);
//            return NULL;
//        }
//    }
//
//    return copy1;
//}

#endif //FUNDAMENTAL_ALGORITHMS_OVERLOAD_HEAP_H
