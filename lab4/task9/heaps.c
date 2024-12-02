#include "heaps.h"

const heap_functions HEAP_IMPLEMENTATIONS[] = {
        {   // Binary Heap
                .create_heap = (Q_queue *(*)())create_binary_heap,
                .insert = (int (*)(Q_queue *, Ticket))insert_binary_heap,
                .extract_max = (int (*)(Q_queue *, Ticket *))extract_max_binary_heap,
                .merge = NULL,
                .destroy = (void (*)(Q_queue *))destroy_binary_heap,
                .merge_with_copy = NULL
        },
        {   // Leftist Heap
                .create_heap = (Q_queue *(*)())create_leftist_heap,
                .insert = (int (*)(Q_queue *, Ticket))insert_leftist_heap,
                .extract_max = (int (*)(Q_queue *, Ticket *))extract_max_leftist_heap,
                .merge = (int (*)(Q_queue *, Q_queue *, Q_queue *))merge_leftist_heap_errcode,
                .destroy = (void (*)(Q_queue *))destroy_leftist_heap,
                .merge_with_copy = (int (*)(Q_queue *, Q_queue *, Q_queue *))merge_leftist_heap_with_copy
        },
        {   // Skew Heap
                .create_heap = (Q_queue *(*)())create_skew_heap,
                .insert = (int (*)(Q_queue *, Ticket))insert_skew_heap,
                .extract_max = (int (*)(Q_queue *, Ticket *))extract_max_skew_heap,
                .merge = (int (*)(Q_queue *, Q_queue *, Q_queue *))merge_skew_heap_errcode,
                .destroy = (void (*)(Q_queue *))destroy_skew_heap,
                .merge_with_copy = (int (*)(Q_queue *, Q_queue *, Q_queue *))merge_skew_heap_with_copy
        },
        {   // Binomial Heap
                .create_heap = (Q_queue *(*)())create_binomial_heap,
                .insert = (int (*)(Q_queue *, Ticket))insert_binomial_heap,
                .extract_max = (int (*)(Q_queue *, Ticket *))extract_max_binomial_heap,
                .merge = (int (*)(Q_queue *, Q_queue *, Q_queue *))merge_binomial_heap_errcode,
                .destroy = (void (*)(Q_queue *))destroy_binomial_heap,
                .merge_with_copy = (int (*)(Q_queue *, Q_queue *, Q_queue *))merge_binomial_heap_with_copy
        },
        {   // Fibonacci Heap
                .create_heap = (Q_queue *(*)())create_fibonacci_heap,
                .insert = (int (*)(Q_queue *, Ticket))insert_fibonacci_heap,
                .extract_max = (int (*)(Q_queue *, Ticket *))extract_max_fibonacci_heap,
                .merge = (int (*)(Q_queue *, Q_queue *, Q_queue *))merge_fibonacci_heap_errcode,
                .destroy = (void (*)(Q_queue *))destroy_fibonacci_heap,
                .merge_with_copy = (int (*)(Q_queue *, Q_queue *, Q_queue *))merge_fibonacci_heap_with_copy
        },
        {   // Treap
                .create_heap = (Q_queue *(*)())create_treap,
                .insert = (int (*)(Q_queue *, Ticket))insert_treap,
                .extract_max = (int (*)(Q_queue *, Ticket *))extract_max_treap,
                .merge = (int (*)(Q_queue *, Q_queue *, Q_queue *))merge_treap_errcode,
                .destroy = (void (*)(Q_queue *))destroy_treap,
                .merge_with_copy = (int (*)(Q_queue *, Q_queue *, Q_queue *))merge_treap_with_copy
        }
};

int merge_leftist_heap_errcode(LeftistHeap *a, LeftistHeap *b, LeftistHeap *result) {
    result->head = merge_leftist_heap(a->head, b->head);
    if (!result->head)
        return throw_err(MEMORY_NOT_ALLOCATED);

    return 0;
}

int merge_skew_heap_errcode(SkewHeap *a, SkewHeap *b, SkewHeap *result) {
    result->head = merge_skew_heap(a->head, b->head);
    if (!result->head)
        return throw_err(MEMORY_NOT_ALLOCATED);

    return 0;
}

int merge_binomial_heap_errcode(BinomialHeap *a, BinomialHeap *b, BinomialHeap *result) {
    result->head = merge_binomial_heap(a->head, b->head);
    if (!result->head)
        return throw_err(MEMORY_NOT_ALLOCATED);

    return 0;
}

int merge_fibonacci_heap_errcode(FibonacciHeap *a, FibonacciHeap *b, FibonacciHeap *result) {
    result = copy_fibonacci_heap(a);
    if (!result)
        return throw_err(MEMORY_NOT_ALLOCATED);

    return merge_fibonacci_heap(&result, b);
}

int merge_treap_errcode(Treap *a, Treap *b, Treap *result) {
    result->head = merge_treap(a->head, b->head);
    if (!result->head)
        return throw_err(MEMORY_NOT_ALLOCATED);

    return 0;
}
