#include "treap.h"

TreapNode *create_treap_node(Ticket ticket) {
    TreapNode *new_node = (TreapNode *) calloc(1, sizeof(TreapNode));
    if (!new_node)
        return NULL;

    new_node->ticket = ticket;
    copy_newstr(&new_node->ticket.key, &ticket.key);

    return new_node;
}

Treap *create_treap() {
    Treap *new_treap = calloc(1, sizeof(Treap));

    return new_treap;
}

int split_treap(TreapNode *head, String key, TreapNode **result1, TreapNode **result2) {
    if (!head) {
        *result1 = NULL;
        *result2 = NULL;
        return 0;
    }

    TreapNode *temp1 = NULL, *temp2 = NULL;
    if (compare_str(key, head->ticket.key) > 0) {
        split_treap(head->right, key, &temp1, &temp2);
        head->right = temp1;
        *result1 = head;
        *result2 = temp2;
        return 0;
    }
    else {
        split_treap(head->left, key, &temp1, &temp2);
        head->left = temp2;
        *result1 = temp1;
        *result2 = head;
        return 0;
    }
}

TreapNode *merge_treap(TreapNode *a, TreapNode *b) {
    if (!a)
        return b;
    else if (!b)
        return a;

    if (a->ticket.priority > b->ticket.priority) {
        a->right = merge_treap(a->right, b);
        return a;
    } else {
        b->left = merge_treap(a, b->left);
        return b;
    }
}

int insert_treap(Treap *head, Ticket ticket) {
    TreapNode *temp1 = NULL, *temp2 = NULL;

    TreapNode *new_node = create_treap_node(ticket);
    if (!new_node)
        return throw_err(MEMORY_NOT_ALLOCATED);

    split_treap(head->head, ticket.key, &temp1, &temp2);

    head->head = merge_treap(merge_treap(temp1, new_node), temp2);

    head->size++;

    return 0;
}

int extract_max_treap(Treap *head, Ticket *res) {
    if (head->size <= 0)
        return throw_err(OUT_OF_BOUNDS);

    TreapNode *max = head->head;

    head->head = merge_treap(max->left, max->right);

    *res = max->ticket;
    free(max);

    head->size--;

    return 0;
}

Ticket get_max_treap(Treap *head) {
    return head->head->ticket;
}

TreapNode *copy_treap_node(TreapNode *node) {
    if (!node)
        return NULL;

    TreapNode *new_node = (TreapNode *)calloc(1, sizeof(TreapNode));
    if (!new_node)
        return NULL;

    new_node->ticket = node->ticket;
    new_node->left = copy_treap_node(node->left);
    new_node->right = copy_treap_node(node->right);

    return new_node;
}

Treap *copy_treap(Treap *original) {
    if (!original)
        return NULL;

    Treap *new_treap = (Treap *)calloc(1, sizeof(Treap));
    if (!new_treap)
        return NULL;

    new_treap->head = copy_treap_node(original->head);
    new_treap->size = original->size;

    return new_treap;
}

int merge_treap_with_copy(Treap *treap1, Treap *treap2, Treap *result) {
    if (!treap1 || !treap2)
        return throw_err(INCORRECT_ARGUMENTS);

    Treap *copy1 = copy_treap(treap1);
    if (!copy1)
        return throw_err(MEMORY_NOT_ALLOCATED);

    Treap *copy2 = copy_treap(treap2);
    if (!copy2) {
        destroy_treap(copy1);
        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    result->head = merge_treap(copy1->head, copy2->head);
    result->size = copy1->size + copy2->size;

    free(copy1);
    free(copy2);

    return 0;
}

void destroy_treap_node(TreapNode *node) {
    if (!node)
        return;

    destroy_treap_node(node->left);
    destroy_treap_node(node->right);

    destroy_str(&node->ticket.key);

    free(node);
}

void destroy_treap(Treap *treap) {
    if (!treap)
        return;

    destroy_treap_node(treap->head);
    free(treap);
}
