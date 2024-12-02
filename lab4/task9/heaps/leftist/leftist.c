#include "leftist.h"

LeftistHeap *create_leftist_heap() {
    LeftistHeap *heap = (LeftistHeap *)calloc(1, sizeof(LeftistHeap));
    if (!heap)
        return NULL;

    return heap;
}

LeftistNode *create_leftist_node(Ticket ticket) {
    LeftistNode *res = (LeftistNode *)calloc(1, sizeof(LeftistNode));
    if (!res)
        return NULL;

    res->ticket = ticket;
    copy_newstr(&res->ticket.key, &ticket.key);

    return res;
}

void swap_nodes_leftist(LeftistNode **node1, LeftistNode **node2) {
    LeftistNode *temp;
    temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}

void destroy_leftist_nodes(LeftistNode *root) {
    if (!root)
        return;

    if (root->left) {
        destroy_leftist_nodes(root->left);
        root->left = NULL;
    }

    if (root->right) {
        destroy_leftist_nodes(root->right);
        root->right = NULL;
    }

    destroy_str(&root->ticket.key);
    free(root);
}

void destroy_leftist_heap(LeftistHeap *heap) {
    if (!heap)
        return;

    destroy_leftist_nodes(heap->head);
    free(heap);
}

LeftistNode *merge_leftist_heap(LeftistNode *head1, LeftistNode *head2) {
    if (!head1) {
        if (!head2)
            return NULL;
        head2->NPL = 0;
        return head2;
    } else if (!head2) {
        head1->NPL = 0;
        return head1;
    }

    if (head1->ticket.priority > head2->ticket.priority) {
        LeftistNode* merged_right = merge_leftist_heap(head1->right, head2);
        if (!merged_right) {
            return head1;
        }

        head1->right = merged_right;

//        if (!head1->right) {
//            destroy_leftist_nodes(head1);
//            free(head1);
//            return NULL;
//        }

        if (!head1->left || head1->left->NPL < head1->right->NPL) {
            swap_nodes_leftist(&head1->left, &head1->right);
        }

        if (head1->right)
            head1->NPL = head1->right->NPL + 1;

        return head1;
    } else {
        LeftistNode* merged_right = merge_leftist_heap(head2->right, head1);
        if (!merged_right) {
            return head2;
        }

        head2->right = merged_right;

//        if (!head2->right) {
//            destroy_leftist_nodes(head2);
//            free(head2);
//            return NULL;
//        }

        if (!head2->left || head2->left->NPL < head2->right->NPL) {
            swap_nodes_leftist(&head2->left, &head2->right);
        }

        if (head2->right)
            head2->NPL = head2->right->NPL + 1;

        return head2;
    }
}

//LeftistNode *merge_leftist_heap(LeftistNode *head1, LeftistNode *head2) {
//    LeftistNode *new;
//
//    if (!head1) {
//        if (!head2)
//            return NULL;
//        head2->NPL = 0;
//        return head2;
//    } else if (!head2) {
//        head1->NPL = 0;
//        return head1;
//    }
//
//    if (head1->ticket.priority > head2->ticket.priority) {
//        new = create_leftist_node(head1->ticket);
//        if (!new)
//            return NULL;
//
//        new->left = head1->left;
//        new->right = merge_leftist_heap(head1->right, head2);
//
//        destroy_str(&head1->ticket.key);
//        free(head1);
//    } else {
//        new = create_leftist_node(head2->ticket);
//        if (!new)
//            return NULL;
//
//        new->left = head2->left;
//        new->right = merge_leftist_heap(head2->right, head1);
//
//        destroy_str(&head2->ticket.key);
//        free(head2);
//    }
//    if (!new->right) {
//        free(new);
//        return NULL;
//    }
//
//    if (!new->left || new->left->NPL < new->right->NPL) {
//        swap_nodes_leftist(&new->left, &new->right);
//    }
//
//    if (new->right)
//        new->NPL = new->right->NPL + 1;
//
//
//    return new;
//}

int insert_leftist_heap(LeftistHeap *heap, Ticket ticket) {
    LeftistNode *new_node = create_leftist_node(ticket);
    if (!new_node)
        return throw_err(MEMORY_NOT_ALLOCATED);

    LeftistNode *merged = merge_leftist_heap(heap->head, new_node);
    if (!merged) {
        destroy_str(&new_node->ticket.key);
        free(new_node);
        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    heap->head = merged;
    heap->size++;
    return 0;
}

int extract_max_leftist_heap(LeftistHeap *heap, Ticket *result) {
    if (!heap || heap->size == 0)
        return throw_err(OUT_OF_BOUNDS);

    *result = heap->head->ticket;
    LeftistNode *temp = merge_leftist_heap(heap->head->left, heap->head->right);
    free(heap->head);
    heap->head = temp;
    heap->size--;

    return 0;
}

Ticket get_max_leftist_heap(LeftistHeap *heap) {
    return heap->head->ticket;
}


LeftistNode* copy_leftist_node(LeftistNode* node) {
    if (!node) return NULL;

    LeftistNode* new_node = create_leftist_node(node->ticket);
    if (!new_node) return NULL;

    new_node->NPL = node->NPL;
    new_node->left = copy_leftist_node(node->left);
    new_node->right = copy_leftist_node(node->right);

    return new_node;
}

LeftistHeap* copy_leftist_heap(LeftistHeap* heap) {
    if (!heap) return NULL;

    LeftistHeap* new_heap = create_leftist_heap();
    if (!new_heap) return NULL;

    new_heap->head = copy_leftist_node(heap->head);
    new_heap->size = heap->size;

    return new_heap;
}

int merge_leftist_heap_with_copy(LeftistHeap *heap1, LeftistHeap *heap2, LeftistHeap *result) {
    LeftistHeap* copy1 = copy_leftist_heap(heap1);
    LeftistHeap* copy2 = copy_leftist_heap(heap2);

    if (!copy1 || !copy2) {
        destroy_leftist_heap(copy1);
        destroy_leftist_heap(copy2);
        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    result->head = merge_leftist_heap(copy1->head, copy2->head);
    result->size = copy1->size + copy2->size;

    free(copy2);
    free(copy1);
    return 0;
}

