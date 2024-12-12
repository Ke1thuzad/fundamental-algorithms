#ifndef FUNDAMENTAL_ALGORITHMS_TICKET_H
#define FUNDAMENTAL_ALGORITHMS_TICKET_H

#include "../../lab3/task4/mystring.h"

typedef struct Time {
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int second;
} Time;

typedef struct Ticket {
    Time submit_time;
    int priority;
    String key;  // Dept ID
    String value;  // Ticket Content
} Ticket;

typedef struct BinaryHeap BinaryHeap;
typedef struct LeftistHeap LeftistHeap;
typedef struct SkewHeap SkewHeap;
typedef struct BinomialHeap BinomialHeap;
typedef struct FibonacciHeap FibonacciHeap;
typedef struct Treap Treap;

typedef enum HeapType {
    BINARY,
    LEFTIST,
    SKEW,
    BINOMIAL,
    FIBONACCI,
    TREAP
} HeapType;

typedef union Q_queue {
    BinaryHeap *binary_heap;
    LeftistHeap *leftist_heap;
    SkewHeap *skew_heap;
    BinomialHeap *binomial_heap;
    FibonacciHeap *fibonacci_heap;
    Treap *treap;
} Q_queue;

typedef struct heap_functions {
    Q_queue *(*create_heap)();
    int (*insert)(Q_queue *queue, Ticket ticket);
    int (*merge)(Q_queue *queue1, Q_queue *queue2, Q_queue *result);
    int (*merge_with_copy)(Q_queue *queue1, Q_queue *queue2, Q_queue *result);
    int (*extract_max)(Q_queue *queue, Ticket *result);
    Ticket (*get_max_priority)(Q_queue *queue);
    size_t (*get_size)(Q_queue *queue);
    void (*destroy)(Q_queue *queue);
} heap_functions;


extern const heap_functions HEAP_IMPLEMENTATIONS[];



#endif //FUNDAMENTAL_ALGORITHMS_TICKET_H
