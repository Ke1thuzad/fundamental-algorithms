#include "../../main.h"
#include "binomial.h"

BinomialNode *create_binomial_node(Ticket ticket) {
    BinomialNode *new_node = (BinomialNode *) calloc(1, sizeof(BinomialNode));
    if (!new_node)
        return NULL;

    if (ticket.key.val) {
        new_node->ticket = ticket;
        copy_newstr(&new_node->ticket.key, &ticket.key);
        copy_newstr(&new_node->ticket.value, &ticket.value);
    }

    return new_node;
}

BinomialNode *simple_merge_binomial_heap(BinomialNode *head1, BinomialNode *head2) {
    if (!head1)
        return head2;
    if (!head2)
        return head1;

    BinomialNode *res = create_binomial_node((Ticket) {{}, 0, 0, 0}), *reshead = res;
    if (!res)
        return NULL;

    BinomialNode *A = head1, *B = head2;

    while (A) {
        if (A->degree <= B->degree) {
            BinomialNode *temp = A;
            res->sibling = A;
            A = temp->sibling;
            res->sibling->sibling = NULL;
            res = res->sibling;
        } else {
            BinomialNode *temp = A;
            A = B;
            B = temp;
        }
    }

    res->sibling = B;

    res = reshead->sibling;

    free(reshead);

    return res;
}

void adopt_binomial_tree(BinomialNode *parent, BinomialNode *child) {
    BinomialNode *prev_child = parent->child;
    parent->child = child;
    child->sibling = prev_child;
    child->parent = parent;
    parent->degree = child->degree + 1;

//    return parent;
}

/*
Аккуратно, в алгоритме минимизируем, а в коде максимизируем!!!
ПОЛНЫЕ АЛГОРИТМЫ:
    Вариант 1:
        1. Соединяем 2 кучи в одну результирующую в невозрастающем порядке степеней.
        2. Проходим по результирующей куче и проверяем, что степени биноминальных деревьев (degree) совпадают.
        2.1. Если степени совпадают, но есть еще один элемент с такой же степенью, то ничего не меняем и идем на следующие элементы.
        2.2. Если степени совпадают и больше нет элементов с такой степенью (а это мы гарантируем, т.к. в 1 шаге так соединяли), то к наименьшему элементу в детей цепляем другой. Указатель наименьшего элемента не меняем!
        3. Если не совпадают, то переходим к следующим 2 подряд идущим элементам.

    Вариант 1 (Полный алгоритм): (Пусть H1, H2 - кучи для merge)
        1. Создаем результирующую кучу Res путем простого слияния куч H1 и H2 в порядке неубывания степеней деревьев (simple_merge_binomial_heap)
        2. Инициализируем указатели:
           - prev = NULL (предыдущий узел)
           - cur = начало Res (текущий узел)
           - next = следующий узел
        3. Пока next существует:
           - Если степени cur и next различны ИЛИ есть третье дерево такой же степени:
             * prev = cur
             * cur = next
           - Иначе:
             * Если ключ cur >= ключ next:
               + Присоединяем next как ребенка к cur и ставим правильно следующий элемент.
             * Иначе:
               + Если prev == NULL:
                 - Res = next
               + Иначе:
                 - prev->sibling = next
               + Присоединяем cur как ребенка к next
               + cur = next
           - next = cur->sibling
        4. Возвращаем Res
*/
BinomialNode *merge_binomial_heap(BinomialNode *head1, BinomialNode *head2) {
    BinomialNode *res = simple_merge_binomial_heap(head1, head2);
    if (!res)
        return res;

    BinomialNode *prev, *cur, *next;

    prev = NULL;
    cur = res;
    next = res->sibling;

    while (next) {
        if (cur->degree != next->degree || (next->sibling && next->sibling->degree == cur->degree)) {
            prev = cur;
            cur = next;
        } else {
            if (cur->ticket.priority >= next->ticket.priority) {
                cur->sibling = next->sibling;
                adopt_binomial_tree(cur, next);
            } else {
                if (!prev) {
                    res = next;
                } else {
                    prev->sibling = next;
                }
                adopt_binomial_tree(next, cur);
                cur = next;
            }
        }
        next = cur->sibling;
    }

    return res;
}

int insert_binomial_heap(BinomialHeap *heap, Ticket ticket) {
    BinomialNode *new_node = create_binomial_node(ticket);
    if (!new_node)
        return throw_err(MEMORY_NOT_ALLOCATED);

    heap->head = merge_binomial_heap(heap->head, new_node);
    if (!heap->head)
        return throw_err(MEMORY_NOT_ALLOCATED);

    heap->size++;

    return 0;
}

int test_binomial_heap(BinomialNode *heap) {
    if (heap == NULL)
        return 0;

    if (heap->parent && heap->ticket.priority < heap->parent->ticket.priority)
        return throw_err(INCORRECT_ARGUMENTS);

    int err = test_binomial_heap(heap->child);
    if (err)
        return err;

    err = test_binomial_heap(heap->sibling);
    if (err)
        return err;

    return 0;
}

BinomialHeap* create_binomial_heap() {
    BinomialHeap *heap = (BinomialHeap *)calloc(1, sizeof(BinomialHeap));
    if (!heap)
        return NULL;

    return heap;
}

BinomialNode* copy_binomial_node(BinomialNode* node) {
    if (!node) return NULL;

    BinomialNode* new_node = create_binomial_node(node->ticket);
    if (!new_node) return NULL;

    new_node->degree = node->degree;
    new_node->child = copy_binomial_node(node->child);
    new_node->sibling = copy_binomial_node(node->sibling);

    return new_node;
}

BinomialHeap* copy_binomial_heap(BinomialHeap* heap) {
    if (!heap) return NULL;

    BinomialHeap* new_heap = create_binomial_heap();
    if (!new_heap) return NULL;

    new_heap->head = copy_binomial_node(heap->head);
    new_heap->size = heap->size;

    return new_heap;
}

int merge_binomial_heap_with_copy(BinomialHeap *heap1, BinomialHeap *heap2, BinomialHeap *result) {
    BinomialHeap* copy1 = copy_binomial_heap(heap1);
    BinomialHeap* copy2 = copy_binomial_heap(heap2);

    if (!copy1 || !copy2) {
        destroy_binomial_heap(copy1);
        destroy_binomial_heap(copy2);
        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    result->head = merge_binomial_heap(copy1->head, copy2->head);
    result->size = copy1->size + copy2->size;

    free(copy2);
    free(copy1);
    return 0;
}

void destroy_binomial_heap(BinomialHeap* heap) {
    if (!heap) return;
    destroy_binomial_node(heap->head);
    free(heap);
}

void destroy_binomial_node(BinomialNode* node) {
    if (!node) return;

    destroy_str(&node->ticket.key);

    destroy_binomial_node(node->child);
    destroy_binomial_node(node->sibling);

    free(node);
}

int count_nodes_binomial_heap(BinomialNode *head) {
    if (!head)
        return 0;

    int count = 0;
    BinomialNode *cur = head;

    while (cur) {
        count += (1 << cur->degree);
        cur = cur->sibling;
    }

    return count;
}

BinomialNode *get_max_binomial_heap(BinomialNode *head) {
    if (!head)
        return NULL;

    BinomialNode *max_node = head;
    BinomialNode *cur = head->sibling;

    while (cur) {
        if (cur->ticket.priority > max_node->ticket.priority) {
            max_node = cur;
        }
        cur = cur->sibling;
    }

    return max_node;
}

Ticket get_max_priority_binomial_heap(BinomialHeap *heap) {
    return get_max_binomial_heap(heap->head)->ticket;
}

int extract_max_binomial_heap(BinomialHeap *heap, Ticket *result) {
    if (!heap->head || heap->size <= 0)
        return throw_err(OUT_OF_BOUNDS);

    BinomialNode *max_node = get_max_binomial_heap(heap->head);
    BinomialNode *prev = NULL;
    BinomialNode *cur = heap->head;

    while (cur != max_node) {
        prev = cur;
        cur = cur->sibling;
    }

    if (prev) {
        prev->sibling = max_node->sibling;
    } else {
        heap->head = max_node->sibling;
    }

    heap->size--;

    BinomialNode *new_head = NULL;
    BinomialNode *child = max_node->child;
    BinomialNode *next_child;

    while (child) {
        next_child = child->sibling;
        child->sibling = new_head;
        child->parent = NULL;
        new_head = child;
        child = next_child;
    }

    *result = max_node->ticket;

    heap->head = merge_binomial_heap(heap->head, new_head);

    free(max_node);

    return 0;
}

void print_binomial_tree(BinomialNode *node, int level) {
    if (!node)
        return;

    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("%d (degree: %d)\n", node->ticket.priority, node->degree);

    BinomialNode *child = node->child;
    while (child) {
        print_binomial_tree(child, level + 1);
        child = child->sibling;
    }
}

void print_binomial_heap(BinomialNode *head) {
    if (!head) {
        printf("Binomial heap is empty.\n");
        return;
    }

    BinomialNode *cur = head;
    while (cur) {
        printf("Binomial tree of degree %d:\n", cur->degree);
        print_binomial_tree(cur, 0);
        cur = cur->sibling;
    }
}

size_t get_size_binomial_heap(BinomialHeap *heap) {
    return heap->size;
}
