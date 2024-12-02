#include "main.h"

// Helper function to create a Ticket
Ticket create_ticket(int priority, int department_id, char *key) {
    Ticket ticket;
    ticket.submit_time.day = 1;
    ticket.submit_time.month = 1;
    ticket.submit_time.year = 2023;
    ticket.submit_time.hour = 0;
    ticket.submit_time.minute = 0;
    ticket.submit_time.second = 0;
    ticket.priority = priority;
    ticket.department_id = department_id;
    create_str(&ticket.key, key);
    return ticket;
}

// Helper function to compare integers in descending order
int compare_int_desc(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

void print_ticket(Ticket* ticket) {
    printf("Priority: %d, Department: %d, Time: %02d:%02d:%02d %02d/%02d/%d, Key: %s\n",
           ticket->priority,
           ticket->department_id,
           ticket->submit_time.hour,
           ticket->submit_time.minute,
           ticket->submit_time.second,
           ticket->submit_time.day,
           ticket->submit_time.month,
           ticket->submit_time.year,
           ticket->key.val);
}

Ticket create_test_ticket(int priority, int dept_id, char* key_prefix, int index) {
    Ticket ticket;
    ticket.submit_time = (Time){1, 1, 2024, 12, index, 0};
    ticket.priority = priority;
    ticket.department_id = dept_id;
    create_str(&ticket.key, key_prefix);
    append_str(&ticket.key, '0' + index);
    return ticket;
}

void test_basic_operations(const heap_functions* funcs, Q_queue* queue) {
    printf("\nTesting basic insert/extract:\n");

    Ticket tickets[5];
    for(int i = 0; i < 5; i++) {
        tickets[i] = create_test_ticket((5-i) * 10, i+1, "Basic", i);
        printf("Inserting: ");
        print_ticket(&tickets[i]);
        funcs->insert(queue, tickets[i]);
        destroy_str(&tickets[i].key);
    }

    printf("\nExtracting all elements:\n");
    Ticket result;
    while(funcs->extract_max(queue, &result) == 0) {
        print_ticket(&result);
        destroy_str(&result.key);
    }
}

void test_merge_operations(const heap_functions* funcs) {
    if (!funcs->merge_with_copy || !funcs->merge)
        return;

    printf("\nTesting merge operations:\n");

    Q_queue *queue1, *queue2, *merged;
    queue1 = funcs->create_heap();
    queue2 = funcs->create_heap();
    merged = funcs->create_heap();

    // Fill first queue
    Ticket tickets1[3];
    for(int i = 0; i < 3; i++) {
        tickets1[i] = create_test_ticket(50 - i*10, i+1, "Q1_", i);
        funcs->insert(queue1, tickets1[i]);
        destroy_str(&tickets1[i].key);
    }

    // Fill second queue
    Ticket tickets2[3];
    for(int i = 0; i < 3; i++) {
        tickets2[i] = create_test_ticket(45 - i*10, i+4, "Q2_", i);
        funcs->insert(queue2, tickets2[i]);
        destroy_str(&tickets2[i].key);
    }

    printf("Merging queues...\n");
    funcs->merge_with_copy(queue1, queue2, merged);

    printf("Merged queue contents:\n");
    Ticket result;
    while(funcs->extract_max(merged, &result) == 0) {
        print_ticket(&result);
        destroy_str(&result.key);  // REMOVE IF TREAP
    }

    funcs->destroy(queue1);
    funcs->destroy(queue2);
    funcs->destroy(merged);
}

void test_heap(const heap_functions* funcs, const char* heap_name) {
    printf("\n=== Testing %s ===\n", heap_name);

    Q_queue *queue;
    queue = funcs->create_heap();

    test_basic_operations(funcs, queue);
    test_merge_operations(funcs);

    funcs->destroy(queue);
}

int main() {
    TrieNode* root = create_trie_node('\0');

    // Create test departments
    String id1, id2, id3, id4, id5;
    create_str(&id1, "DEP1");
    create_str(&id2, "DEP2");
    create_str(&id3, "DOG");
    create_str(&id4, "DOOR");
    create_str(&id5, "DORITOS");


    Department* dep1 = create_department(id1, BINARY, 5, 0.8f);
    Department* dep2 = create_department(id2, BINARY, 3, 0.7f);
    Department* dep3 = create_department(id3, BINARY, 3, 0.7f);
    Department* dep4 = create_department(id4, BINARY, 3, 0.7f);
    Department* dep5 = create_department(id5, BINARY, 3, 0.7f);

    insert_department_trie_node(root, dep1);
    insert_department_trie_node(root, dep2);
    insert_department_trie_node(root, dep3);
    insert_department_trie_node(root, dep4);
    insert_department_trie_node(root, dep5);

//    printf("Starting comprehensive heap tests...\n");
//
//    const char* HEAP_NAMES[] = {
//            "Leftist Heap",
//            "Skew Heap",
//            "Binary Heap",
//            "Fibonacci Heap",
//            "Binomial Heap",
//            "Treap"
//    };
//
//    const int NUM_HEAPS = sizeof(HEAP_NAMES) / sizeof(HEAP_NAMES[0]);
//
//    for (int i = 0; i < NUM_HEAPS; i++) {
//        test_heap(&HEAP_IMPLEMENTATIONS[i], HEAP_NAMES[i]);
//    }
//
//    printf("\nAll heap tests completed successfully.\n");
    return 0;
}
