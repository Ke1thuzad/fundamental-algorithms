#ifndef FUNDAMENTAL_ALGORITHMS_DEPARTMENT_STRUCTURE_H
#define FUNDAMENTAL_ALGORITHMS_DEPARTMENT_STRUCTURE_H

#include "../ticket.h"

typedef struct Operator Operator;

typedef struct Department {
    String id;
    Q_queue *priority_queue;
    heap_functions heap_funcs;
    int total_operators;
    int occupied_operators;
    float overload_coefficient;  // TODO: not needed?
    Operator *operators;
} Department;

typedef struct Operator {
    Department *department;
    String name;
    unsigned char is_occupied;
    Ticket *current_ticket;
    int remaining_time;
} Operator;

#endif //FUNDAMENTAL_ALGORITHMS_DEPARTMENT_STRUCTURE_H
