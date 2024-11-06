#include "main.h"

int create_stack(UndoStack *stack) {
    stack->val = (Change *) malloc(sizeof(Change) * 5);
    if (!stack->val)
        return throw_err(MEMORY_NOT_ALLOCATED);

    stack->length = 0;
    stack->capacity = 5;

    return 0;
}

int push_stack(UndoStack *stack, Change change) {
    if (stack->length + 1 >= stack->capacity) {
        int err = resize_stack(stack, stack->capacity);
        if (err)
            return err;
    }

    Change *new = &stack->val[stack->length++];

    new->changed = malloc(sizeof(Liver));
    new->old = malloc(sizeof(Liver));


    new->cmd = change.cmd;

    if (change.old)
        copy_liver(new->old, change.old);
    if (change.changed)
        copy_liver(new->changed, change.changed);
    
    return 0;
}

int resize_stack(UndoStack *stack, int size_delta) {
    Change* new_addr = (Change*) realloc(stack->val, stack->capacity + size_delta * sizeof(Change));

    if (!new_addr) {
        free(stack->val);
        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    stack->val = new_addr;
    stack->capacity += size_delta;
    return 0;
}

Change* pop_stack(UndoStack *stack) {
    if (stack->length > 0)
        return &stack->val[stack->length--];

    return NULL;
}

void destroy_stack(UndoStack *stack) {
    while (stack->length > 0) {
        Change *change = pop_stack(stack);

        destroy_liver(change->changed);
        destroy_liver(change->old);
    }

    if (stack->val) {
        free(stack->val);
        stack->val = NULL;
    }

    stack->length = 0;
    stack->capacity = 0;
}