#ifndef FUNDAMENTAL_ALGORITHMS_ERROR_HANDLER_H
#define FUNDAMENTAL_ALGORITHMS_ERROR_HANDLER_H

#include <stdio.h>
#include <stdlib.h>

typedef enum errcode {
    OUT_OF_BOUNDS = 2,
    NOT_A_NUMBER,
    INCORRECT_OPTION,
    INCORRECT_ARGUMENTS,
    MEMORY_NOT_ALLOCATED
} errcode;

void throw_err(errcode err);

#endif //FUNDAMENTAL_ALGORITHMS_ERROR_HANDLER_H
