#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include "../../utility/error_handler.h"
#include "../../utility/overio.h"

#include <string.h>
#include <stdio.h>

typedef enum Command {
    SUM,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    MODULUS,
    EVALUATION,
    DIFFERENTIATION,
    COMPOSITION
} Command;

typedef struct List {
    int val;
    struct List *next;
} List;

typedef struct Polynomial {
    int n;
    List *head;
} Polynomial;

// Polynomial Functions
List* create_node(int val);
int prepend_list(List **list, int val);
int append_list(List **list, int val);
int delete_node(List **list, List *addr);
int copy_list(List **dst, List *src);

int search_polynomial_power(Polynomial *a, int val, int power, int max_power);
int prepend_polynomial(Polynomial *head, int val);
int append_polynomial(Polynomial *head, int val);
void print_polynomial(Polynomial head);
void destroy_polynomial(Polynomial *head);
int copy_polynomial(Polynomial *dst, Polynomial src);
void inverse_polynomial(Polynomial *a);

int add_polynomials(Polynomial a, Polynomial b, Polynomial *res);
int subtract_polynomials(Polynomial a, Polynomial b, Polynomial *res);
int inplace_decorator(Polynomial *a, Polynomial b, int (*f)(Polynomial a, Polynomial b, Polynomial *res));
int multiply_coefficient_power(Polynomial a, int coefficient, int power, Polynomial *res);
int multiply_polynomials(Polynomial a, Polynomial b, Polynomial *res);
int complete_division(Polynomial a, Polynomial b, Polynomial *quotient, Polynomial *remainder);
int divide_polynomials(Polynomial a, Polynomial b, Polynomial *res);
int modulus_polynomials(Polynomial a, Polynomial b, Polynomial *res);
int evaluate_point(Polynomial a, int point);
int derive_polynomial(Polynomial a, Polynomial *res);
int compose_polynomials(Polynomial a, Polynomial b, Polynomial *res);


// Calculator functions
int calculator(FILE *in);
int read_command(FILE *in, Command *cmd, int first);
int handle_command(FILE *in, Polynomial *current, Command cmd);
int read_arguments(FILE *in, Array *args, int *n);
int skip_to_semicolon(FILE *in);
int parse_polynomial(Array str, Polynomial *res);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
