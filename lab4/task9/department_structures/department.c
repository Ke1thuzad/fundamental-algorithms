#include "department.h"

String *randomize_operator_name() {
    // TODO: Implement randomization of names. Randomized names must be unique.
    return NULL;
}

Department *create_department(String id, HeapType heap_type, int total_operators, float overload_coefficient) {
    Department *new_department = (Department *) malloc(sizeof(Department));
    if (!new_department)
        return NULL;

    copy_newstr(&new_department->id, &id);

    new_department->heap_type = heap_type;
    new_department->priority_queue = HEAP_IMPLEMENTATIONS[heap_type].create_heap();

    new_department->total_operators = total_operators;
    new_department->occupied_operators = 0;

    new_department->overload_coefficient = overload_coefficient;

    new_department->operators = (Operator *) calloc(total_operators, sizeof(Operator));
    if (!new_department->operators) {
        HEAP_IMPLEMENTATIONS[heap_type].destroy(new_department->priority_queue);
        destroy_str(&new_department->id);

        free(new_department);
        return NULL;
    }

    for (int i = 0; i < total_operators; ++i) {
        Operator *cur_op = &new_department->operators[i];

        cur_op->department = new_department;

        create_str(&cur_op->name, "");
    }

    return new_department;
}

float get_department_load(Department department) {
    return (float) department.occupied_operators / (float) department.total_operators;
}

void destroy_department(Department *department) {
    destroy_str(&department->id);

    HEAP_IMPLEMENTATIONS[department->heap_type].destroy(department->priority_queue);

    for (int i = 0; i < department->total_operators; ++i) {
        Operator *cur_op = &department->operators[i];

        destroy_str(&cur_op->name);
        if (cur_op->is_occupied && cur_op->current_ticket)
            destroy_str(&cur_op->current_ticket->key);
    }
}
