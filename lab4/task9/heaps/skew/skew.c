#include "skew.h"

SkewHeap *create_skew_heap() {
    SkewHeap *heap = (SkewHeap *)calloc(1, sizeof(SkewHeap));
    if (!heap)
        return NULL;

    return heap;
}

SkewNode *create_skew_node(Ticket ticket) {
    SkewNode *res = (SkewNode *)calloc(1, sizeof(SkewNode));
    if (!res)
        return NULL;

    res->ticket = ticket;
    copy_newstr(&res->ticket.key, &ticket.key);
    copy_newstr(&res->ticket.value, &ticket.value);

    return res;
}

void swap_nodes_skew(SkewNode **node1, SkewNode **node2) {
    SkewNode *temp;
    temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}

SkewNode *merge_skew_heap(SkewNode *head1, SkewNode *head2) {
    if (!head1) {
        return head2;
    } else if (!head2) {
        return head1;
    }

    if (head1->ticket.priority < head2->ticket.priority) {
        swap_nodes_skew(&head1, &head2);
    }

    SkewNode *temp = head1->right;
    head1->right = head1->left;
    head1->left = merge_skew_heap(temp, head2);

    return head1;
}

int insert_skew_heap(SkewHeap *heap, Ticket ticket) {
    SkewNode *new_node = create_skew_node(ticket);
    if (!new_node)
        return throw_err(MEMORY_NOT_ALLOCATED);

    heap->head = merge_skew_heap(heap->head, new_node);
    if (!heap->head) {
        destroy_skew_nodes(new_node);
        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    heap->size++;
    return 0;
}

int extract_max_skew_heap(SkewHeap *heap, Ticket *result) {
    if (!heap || heap->size == 0)
        return OUT_OF_BOUNDS;

    *result = heap->head->ticket;
    SkewNode *temp = merge_skew_heap(heap->head->left, heap->head->right);
    free(heap->head);
    heap->head = temp;
    heap->size--;

    return 0;
}

Ticket get_max_skew_heap(SkewHeap *heap) {
    return heap->head->ticket;
}

SkewNode* copy_skew_node(SkewNode* node) {
    if (!node)
        return NULL;

    SkewNode* new_node = create_skew_node(node->ticket);
    if (!new_node)
        return NULL;

    new_node->left = copy_skew_node(node->left);
    new_node->right = copy_skew_node(node->right);

    return new_node;
}

SkewHeap* copy_skew_heap(SkewHeap* heap) {
    if (!heap)
        return NULL;

    SkewHeap* new_heap = create_skew_heap();
    if (!new_heap)
        return NULL;

    new_heap->head = copy_skew_node(heap->head);
    new_heap->size = heap->size;

    return new_heap;
}

int merge_skew_heap_with_copy(SkewHeap *heap1, SkewHeap *heap2, SkewHeap *result) {
    SkewHeap* copy1 = copy_skew_heap(heap1);
    SkewHeap* copy2 = copy_skew_heap(heap2);

    if (!copy1 || !copy2) {
        destroy_skew_heap(copy1);
        destroy_skew_heap(copy2);
        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    result->head = merge_skew_heap(copy1->head, copy2->head);
    result->size = copy1->size + copy2->size;

    free(copy2);
    free(copy1);
    return 0;
}

void destroy_skew_nodes(SkewNode *root) {
    if (!root)
        return;

    if (root->left) {
        destroy_skew_nodes(root->left);
        root->left = NULL;
    }

    if (root->right) {
        destroy_skew_nodes(root->right);
        root->right = NULL;
    }

    destroy_str(&root->ticket.key);
    destroy_str(&root->ticket.value);
    free(root);
}

void destroy_skew_heap(SkewHeap *heap) {
    if (!heap)
        return;

    destroy_skew_nodes(heap->head);
    free(heap);
}

size_t get_size_skew_heap(SkewHeap *heap) {
    return heap->size;
}
