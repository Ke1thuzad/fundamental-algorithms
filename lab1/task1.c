#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

typedef struct Node {
    unsigned char val;
    struct Node* nxt;
} Node;

void process_flag(int, const char*);
void natural_numbers(int);
int is_prime(int);
void to_base16(int);
char to_base16_digits(int);
long long power(int, int);
void exponent_table(int);
void natural_sum(unsigned long long);
void factorial(int);
Node* create_list(unsigned char);
void print_list(const Node*);
void append(Node*, unsigned char);
void append_list(Node*, Node*);
Node* value_to_list(int);
Node* reverse_list(Node*);
void delete_list(Node*);
Node* multiply(Node*, int);

int main(int argc, char** argv) {
    int x;

    if (argc != 3) return 1;

    sscanf_s(argv[1], "%d", &x);

    process_flag(x, argv[2]);

    return 0;
}

void process_flag(int x, const char* flag) {
    if (!strcmp(flag, "-h")) {
        natural_numbers(x);
    } else if(!strcmp(flag, "-p")) {
        if(is_prime(x)) {
            printf_s("%d is a prime number.\n", x);
        } else {
            printf_s("%d is a compound number.\n", x);
        }
    } else if(!strcmp(flag, "-s")) {
        to_base16(x);
    } else if(!strcmp(flag, "-e")) {
        if (x > 10) return; // Error
        exponent_table(x);
    } else if(!strcmp(flag, "-a")) {
        natural_sum(x);
    } else if(!strcmp(flag, "-f")) {
        factorial(x);
    } else {
        // Error
        return;
    }
}

void natural_numbers(int x) {
    unsigned char key = 0;
    for (int i = 1; i < 101; ++i) {
        if (i % x == 0) {
            key = 1;
            printf_s("%d ", i);
        }
    }
    if (!key) printf_s("None");
    printf_s("\n");
}

int is_prime(int x) {
    for (int i = 2; i < x; ++i) {
        if (x % i == 0)
            return 0;
    }
    return 1;
}

void to_base16(int x) {
    int size = (int)(log2(x) * 0.25) + 1, i = size - 1;
    char result[size];

    while (x > 0) {
        result[i--] = to_base16_digits(x);
        x /= 16;
    }

    for (int j = 0; j < size; ++j) {
        if (result[j])
            printf_s("%c ", result[j]);
    }
    printf_s("\n");

}

char to_base16_digits(int x) {
    char letters[6] = "ABCDEF";
    int result = x % 16;
    if (result > 10) return letters[result - 10];
    return '0' + result;
}

void exponent_table(int x) {
    for (int i = 1; i < 11; ++i) {
        for (int j = 1; j <= x; ++j) {
            printf_s("%llu ", power(j, i));
        }
        printf_s("\n");
    }
}

long long power(int x, int y) {
    long long result = x;
    for (int i = 1; i < y; ++i) {
        result *= x;
    }
    return result;
}

void natural_sum(unsigned long long x) {
    unsigned long long result = x;
    for (unsigned long long i = 1; i < x; ++i) {
        result += i;
    }
    printf_s("%llu\n", result);
}

void factorial(int x) {
    Node* result = value_to_list(x);
    for (int i = 1; i < x; ++i) {
        result = multiply(result, i);
    }
    result = reverse_list(result);
    print_list(result);
}

Node* create_list(unsigned char value) {
    Node* head = malloc(sizeof(Node));
    head->val = value;
    head->nxt = NULL;

    return head;
}

void print_list(const Node* head) {
    printf_s("%d", head->val);
    if (head->nxt) print_list(head->nxt);
    else printf_s("\n");
}

void append(Node* head, unsigned char value) {
    if (head->nxt)
        append(head->nxt, value);
    else {
        Node* next_node = malloc(sizeof(Node));
        next_node->val = value;
        next_node->nxt = NULL;

        head->nxt = next_node;
    }
}

void append_list(Node* head, Node* list) {
    if (!list || !head) return;
    if (head->nxt)
        append_list(head->nxt, list);
    else
        head->nxt = list;
}

void delete_list(Node* head) {
    if (head->nxt) {
        delete_list(head->nxt);
        head->nxt = NULL;
    }
    free(head);
}

Node* value_to_list(int value) {
    Node* result = create_list(value % 10);
    value /= 10;
    while (value > 0) {
        append(result, value % 10);
        value /= 10;
    }
    return result;
}

Node* reverse_list(Node* A) {
    Node* reversed_result = NULL;
    while (A) {
        Node* next = A->nxt;
        A->nxt = reversed_result;
        reversed_result = A;
        A = next;
    }

    return reversed_result;
}

Node* multiply(Node* A, int B) {
    Node* result = create_list(0);
    Node* current = A;
    int shift = 0;

    while (current) {
        int product = current->val * B + shift;
        shift = product / 10;
        append(result, product % 10);
        current = current->nxt;
    }

    while (shift > 0) {
        append(result, shift % 10);
        shift /= 10;
    }

    return result->nxt;
}