#include "binary.h"

BinaryHeap *create_binary_heap() {
    BinaryHeap *new_heap = (BinaryHeap *) malloc(sizeof(BinaryHeap));
    if (!new_heap)
        return NULL;

    new_heap->size = 0;
    new_heap->capacity = 10;
    new_heap->heap = (BinaryNode *) calloc(new_heap->capacity, sizeof(BinaryNode));
    if (!new_heap->heap) {
        free(new_heap);
        return NULL;
    }

    return new_heap;
}

int resize_binary_heap(BinaryHeap *heap) {
    BinaryNode *new_heap = (BinaryNode *) realloc(heap->heap, heap->capacity * 2 * sizeof(BinaryNode));
    if (!new_heap) {
        free(heap->heap);
        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    heap->heap = new_heap;
    heap->capacity *= 2;
    return 0;
}

void swap_binary_nodes(BinaryNode *a, BinaryNode *b) {
    BinaryNode temp = *a;
    *a = *b;
    *b = temp;
}

void sift_down_binary_heap(BinaryHeap *heap, int index) {
    while (index * 2 + 1 < heap->size) {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int j = left;

        if (right < heap->size && heap->heap[right].ticket.priority > heap->heap[left].ticket.priority) {
            j = right;
        }
        if (heap->heap[index].ticket.priority >= heap->heap[j].ticket.priority) {
            break;
        }
        swap_binary_nodes(&heap->heap[index], &heap->heap[j]);
        index = j;
    }
}

void sift_up_binary_heap(BinaryHeap *heap, int index) {
    while (heap->heap[index].ticket.priority > heap->heap[(index - 1) / 2].ticket.priority) {
        swap_binary_nodes(&heap->heap[index], &heap->heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

int insert_binary_heap(BinaryHeap *heap, Ticket ticket) {
    if (!heap)
        return throw_err(INCORRECT_ARGUMENTS);

    if (heap->size + 1 >= heap->capacity) {
        int err = resize_binary_heap(heap);
        if (err)
            return err;
    }

    BinaryNode node = {ticket};
    copy_newstr(&node.ticket.key, &ticket.key);
    copy_newstr(&node.ticket.value, &ticket.value);

    heap->heap[heap->size] = node;
    sift_up_binary_heap(heap, heap->size);
    heap->size++;
    return 0;
}

int extract_max_binary_heap(BinaryHeap *heap, Ticket *res) {
    if (heap->size <= 0) {
        return OUT_OF_BOUNDS;
    }

    *res = heap->heap[0].ticket;

    heap->size--;

    heap->heap[0] = heap->heap[heap->size];

    sift_down_binary_heap(heap, 0);

    return 0;
}

Ticket get_max_binary_heap(BinaryHeap *heap) {
    return heap->heap[0].ticket;
}

void destroy_binary_heap(BinaryHeap *heap) {
    if (!heap)
        return;

    if (heap->heap) {
        for (int i = 0; i < heap->size; ++i) {
            destroy_str(&heap->heap[i].ticket.key);
            destroy_str(&heap->heap[i].ticket.value);
        }

        free(heap->heap);
        heap->heap = NULL;
    }

    heap->size = 0;
    heap->capacity = 0;
    free(heap);
}

BinaryHeap *copy_binary_heap(const BinaryHeap *heap) {
    if (!heap)
        return NULL;

    BinaryHeap *new_heap = create_binary_heap();
    if (!new_heap)
        return NULL;

    new_heap->heap = (BinaryNode *) calloc(heap->capacity, sizeof(BinaryNode));
    if (!new_heap->heap) {
        free(new_heap);
        return NULL;
    }

    memcpy(new_heap->heap, heap->heap, heap->size * sizeof(BinaryNode));
    new_heap->size = heap->size;
    new_heap->capacity = heap->capacity;

    return new_heap;
}

int merge_binary_heap(BinaryHeap *heap1, BinaryHeap *heap2, BinaryHeap *result) {
    for (size_t i = 0; i < heap1->size; i++) {
        int err = insert_binary_heap(result, heap1->heap[i].ticket);
        if (err)
            return err;
    }

    for (size_t i = 0; i < heap2->size; i++) {
        int err = insert_binary_heap(result, heap2->heap[i].ticket);
        if (err)
            return err;
    }

    return 0;
}

size_t get_size_binary_heap(BinaryHeap *heap) {
    return heap->size;
}

