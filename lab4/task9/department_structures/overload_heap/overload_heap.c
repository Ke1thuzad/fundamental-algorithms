#include "overload_heap.h"

OverloadBinaryHeap *create_overload_binary_heap() {
    OverloadBinaryHeap *new_heap = (OverloadBinaryHeap *) malloc(sizeof(OverloadBinaryHeap));
    if (!new_heap)
        return NULL;

    new_heap->size = 0;
    new_heap->capacity = 10;
    new_heap->heap = (OverloadNode *) calloc(new_heap->capacity, sizeof(OverloadNode));
    if (!new_heap->heap) {
        free(new_heap);
        return NULL;
    }

    return new_heap;
}

int resize_overload_binary_heap(OverloadBinaryHeap *heap) {
    OverloadNode *new_heap = (OverloadNode *) realloc(heap->heap, heap->capacity * 2 * sizeof(OverloadNode));
    if (!new_heap) {
        free(heap->heap);
        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    heap->heap = new_heap;
    heap->capacity *= 2;
    return 0;
}

void swap_overload_binary_nodes(OverloadNode *a, OverloadNode *b) {
    OverloadNode temp = *a;
    *a = *b;
    *b = temp;
}

void sift_down_overload_binary_heap(OverloadBinaryHeap *heap, int index) {
    float eps = 0.00000001f;

    while (index * 2 + 1 < heap->size) {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int j = left;

        if (right < heap->size && heap->heap[right].overload - heap->heap[left].overload < -eps) {
            j = right;
        }
        if (heap->heap[index].overload - heap->heap[j].overload <= eps) {
            break;
        }
        swap_overload_binary_nodes(&heap->heap[index], &heap->heap[j]);
        index = j;
    }
}

void sift_up_overload_binary_heap(OverloadBinaryHeap *heap, int index) {
    float eps = 0.00000001f;

    while (heap->heap[index].overload - heap->heap[(index - 1) / 2].overload < -eps) {
        swap_overload_binary_nodes(&heap->heap[index], &heap->heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

int insert_overload_binary_heap(OverloadBinaryHeap *heap, Department department) {
    if (!heap || department.id.length == 0)
        return throw_err(INCORRECT_ARGUMENTS);

    if (heap->size + 1 >= heap->capacity) {
        int err = resize_overload_binary_heap(heap);
        if (err)
            return err;
    }

    OverloadNode node = {.overload = get_department_load(department)};
    copy_newstr(&node.id, &department.id);

    heap->heap[heap->size] = node;

    sift_up_overload_binary_heap(heap, heap->size);

    heap->size++;

    return 0;
}

int extract_min_overload_binary_heap(OverloadBinaryHeap *heap, String *id) {
    if (heap->size <= 0) {
        return throw_err(OUT_OF_BOUNDS);
    }

    *id = heap->heap[0].id;  // TODO: отловить утечку?

    heap->size--;

    heap->heap[0] = heap->heap[heap->size];

    sift_down_overload_binary_heap(heap, 0);

    return 0;
}

String get_min_overload_binary_heap(OverloadBinaryHeap *heap) {
    return heap->heap[0].id;
}

void destroy_overload_binary_heap(OverloadBinaryHeap *heap) {
    if (!heap)
        return;

    if (heap->heap) {
        for (int i = 0; i < heap->size; ++i) {
            destroy_str(&heap->heap[i].id);
        }

        free(heap->heap);
        heap->heap = NULL;
    }

    heap->size = 0;
    heap->capacity = 0;

    free(heap);
}

OverloadBinaryHeap *copy_overload_binary_heap(const OverloadBinaryHeap *heap) {
    if (!heap)
        return NULL;

    OverloadBinaryHeap *new_heap = create_overload_binary_heap();
    if (!new_heap)
        return NULL;

    new_heap->heap = (OverloadNode *) calloc(heap->capacity, sizeof(OverloadNode));
    if (!new_heap->heap) {
        free(new_heap);
        return NULL;
    }

    memcpy(new_heap->heap, heap->heap, heap->size * sizeof(OverloadNode));
    new_heap->size = heap->size;
    new_heap->capacity = heap->capacity;

    return new_heap;
}

int change_key_overload_binary_heap(OverloadBinaryHeap *heap, String id, float new_overload) {
    if (!heap || heap->size == 0)
        return throw_err(INCORRECT_ARGUMENTS);

    int index = -1;
    for (size_t i = 0; i < heap->size; i++) {
        if (compare_str(heap->heap[i].id, id) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return 0;
    }

    heap->heap[index].overload = new_overload;

    float eps = 0.00000001f;

    if (index > 0 && heap->heap[index].overload - heap->heap[(index - 1) / 2].overload < -eps) {
        sift_up_overload_binary_heap(heap, index);
    } else {
        sift_down_overload_binary_heap(heap, index);
    }

    return 1;
}

