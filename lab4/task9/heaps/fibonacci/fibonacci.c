#include "fibonacci.h"

FibonacciNode *create_fibonacci_node(Ticket ticket) {
    FibonacciNode *new_node = (FibonacciNode*) calloc(1, sizeof(FibonacciNode));
    if (!new_node)
        return NULL;

    new_node->ticket = ticket;
    copy_newstr(&new_node->ticket.key, &ticket.key);
    copy_newstr(&new_node->ticket.value, &ticket.value);

    return new_node;
}

FibonacciHeap *create_fibonacci_heap() {
    return (FibonacciHeap *) calloc(1, sizeof(FibonacciHeap));
}

int insert_fibonacci_heap(FibonacciHeap *heap, Ticket ticket) {
    FibonacciNode *new_node = create_fibonacci_node(ticket);
    if (!new_node)
        return throw_err(MEMORY_NOT_ALLOCATED);

    if (heap->size == 0) {
        heap->max = new_node;
        heap->max->right = new_node;
        heap->max->left = new_node;
    } else {
        FibonacciNode *prev_right = heap->max->right;
        heap->max->right = new_node;
        new_node->right = prev_right;
        new_node->left = heap->max;
        prev_right->left = new_node;
    }

    if (ticket.priority > heap->max->ticket.priority) {
        heap->max = new_node;
    }

    heap->size++;

    return 0;
}

Ticket get_max_fibonacci_heap(FibonacciHeap *heap) {
    return heap->max->ticket;
}

void union_fibonacci_roots(FibonacciNode *heap1, FibonacciNode *heap2) {
    FibonacciNode *left = heap1->left;
    FibonacciNode *right = heap2->right;

    heap2->right = heap1;
    heap1->left = heap2;
    left->right = right;
    right->left = left;
}

int merge_fibonacci_heap(FibonacciHeap **heap1, FibonacciHeap *heap2) {
    FibonacciHeap *initialHeap = *heap1;

    if (heap2->size == 0)
        return 0;
    else if (initialHeap->size == 0) {
        initialHeap->size = heap2->size;
        initialHeap->max = heap2->max;
    } else {
        union_fibonacci_roots(initialHeap->max, heap2->max);
        initialHeap->size += heap2->size;
    }

    if (!initialHeap->max || (heap2->max->ticket.priority > initialHeap->max->ticket.priority)) {
        initialHeap->max = heap2->max;
    }

    return 0;
}

void link_fibonacci_nodes(FibonacciNode *child, FibonacciNode *parent) {
    child->left->right = child->right;
    child->right->left = child->left;

    child->parent = parent;
    if (parent->child == NULL) {
        parent->child = child;
        child->left = child;
        child->right = child;
    } else {
        child->right = parent->child->right;
        child->left = parent->child;
        parent->child->right->left = child;
        parent->child->right = child;
    }

    parent->degree++;
    child->marked = 0;
}

void consolidate_fibonacci_heap(FibonacciHeap *heap) {
    // Находим максимальный порядок биномиального дерева и выделяем статический массив под деревья
    int max_degree = (int) log2(heap->size) + 1;
    FibonacciNode *degree_trees[max_degree];

    for (int i = 0; i < max_degree; ++i) {
        degree_trees[i] = NULL;
    }

    // Пробегаем полный круг, объединяя все деревья разных порядков

    FibonacciNode *cur = heap->max, *max = heap->max;
    heap->max = NULL;

    do {
        int degree = cur->degree;
        // Пока дерево существует, объединяем его с другими деревьями равной степени
        while (degree_trees[degree] != NULL) {
            FibonacciNode *other = degree_trees[degree];
            if (cur->ticket.priority < other->ticket.priority) {
                FibonacciNode *temp = cur;
                cur = other;
                other = temp;
            }
            if (other == max)
                max = cur;

            link_fibonacci_nodes(other, cur);
            degree_trees[degree] = NULL;
            degree++;
        }

        // Если не существует - записиваем в массив и идем дальше
        degree_trees[degree] = cur;
        cur = cur->right;
    } while (cur != max);

    // Выносим все полученные деревья из массива степеней, обновляем минимум, если необходимо
    for (int i = 0; i < max_degree; ++i) {
        if (degree_trees[i] != NULL) {
            if (heap->max == NULL) {
                heap->max = degree_trees[i];
                heap->max->left = heap->max;
                heap->max->right = heap->max;
            } else {
                FibonacciNode *prev_right = heap->max->right;
                heap->max->right = degree_trees[i];
                degree_trees[i]->right = prev_right;
                degree_trees[i]->left = heap->max;
                prev_right->left = degree_trees[i];

                if (degree_trees[i]->ticket.priority > heap->max->ticket.priority) {
                    heap->max = degree_trees[i];
                }
            }
        }
    }
}

int extract_max_fibonacci_heap(FibonacciHeap *heap, Ticket *result) {
    if (heap->size <= 0)
        return throw_err(OUT_OF_BOUNDS);

    FibonacciNode *max_node = heap->max;
    *result = max_node->ticket;

    if (max_node != NULL) {
        FibonacciNode *child = max_node->child;
        FibonacciNode *next_child;

        // Потрошим детей минимума - пихаем всех в кучу без разбора
        if (child != NULL) {
            do {
                next_child = child->right;
                child->left = heap->max;
                child->right = heap->max->right;
                heap->max->right->left = child;
                heap->max->right = child;
                child->parent = NULL;
                child = next_child;
            } while (child != max_node->child);
        }

        // Закругляем список
        max_node->left->right = max_node->right;
        max_node->right->left = max_node->left;

        // Прореживаем деревья
        if (max_node == max_node->right) {
            heap->max = NULL;
        } else {
            heap->max = max_node->right;
            consolidate_fibonacci_heap(heap);
        }

        heap->size--;
    }

    free(max_node);

    return 0;
}

void destroy_fibonacci_nodes(FibonacciNode *node) {
    if (!node)
        return;

    FibonacciNode *start = node;
    FibonacciNode *current = start;

    do {
        FibonacciNode *next = current->right;
        if (current->child) {
            destroy_fibonacci_nodes(current->child);
        }
        destroy_str(&current->ticket.key);
        free(current);
        current = next;
    } while (current != start);
}

void destroy_fibonacci_heap(FibonacciHeap *heap) {
    if (!heap)
        return;

    FibonacciNode *current = heap->max;

    if (current) {
        FibonacciNode *start = current;
        do {
            FibonacciNode *next = current->right;
            if (current->child) {
                destroy_fibonacci_nodes(current->child);
                free(current->child);
            }
            destroy_str(&current->ticket.key);
            free(current);
            current = next;
        } while (current != start);
    }

    free(heap);
}

FibonacciHeap* copy_fibonacci_heap(FibonacciHeap* heap) {
    if (!heap)
        return NULL;

    FibonacciHeap* new_heap = create_fibonacci_heap();
    if (!new_heap)
        return NULL;

    FibonacciNode *current = heap->max;
    if (current) {
        do {
            insert_fibonacci_heap(new_heap, current->ticket);
            current = current->right;
        } while (current != heap->max);
    }
    return new_heap;
}

int merge_fibonacci_heap_with_copy(FibonacciHeap *heap1, FibonacciHeap *heap2, FibonacciHeap *result) {
    FibonacciHeap *copy1 = copy_fibonacci_heap(heap1);
    FibonacciHeap *copy2 = copy_fibonacci_heap(heap2);

    if (!copy1 || !copy2) {
        destroy_fibonacci_heap(copy1);
        destroy_fibonacci_heap(copy2);
        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    int merge_result = merge_fibonacci_heap(&copy1, copy2);
    if (merge_result != 0) {
        destroy_fibonacci_heap(copy1);
        destroy_fibonacci_heap(copy2);
        return merge_result;
    }

    result->max = copy1->max;
    result->size = copy1->size;

    copy1->max = NULL;
    copy2->max = NULL;
    copy1->size = 0;

    destroy_fibonacci_heap(copy1);
    destroy_fibonacci_heap(copy2);

    return 0;
}

void print_fibonacci_node(FibonacciNode *node, int level) {
    if (!node) return;

    FibonacciNode* start = node;
    FibonacciNode* current = start;

    do {
        // Print indentation based on level
        for (int i = 0; i < level; i++) {
            printf("    ");
        }

        // Print node info
        printf("[%d] %s\n", current->ticket.priority, current->ticket.key.val);

        // Recursively print children
        if (current->child) {
            print_fibonacci_node(current->child, level + 1);
        }

        current = current->right;
    } while (current != start);
}

void print_fibonacci_heap(FibonacciHeap *heap) {
    if (!heap || !heap->max) {
        printf("Empty heap\n");
        return;
    }

    printf("Fibonacci Heap:\n");
    print_fibonacci_node(heap->max, 0);
    printf("Size: %d\n", heap->size);
}

size_t get_size_fibonacci_heap(FibonacciHeap *heap) {
    return heap->size;
}

