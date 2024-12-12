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
//    ticket.department_id = department_id;
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
//           ticket->department_id,
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
//    ticket.department_id = dept_id;
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

void test_storage(const dept_functions* funcs, const char* storage_name) {
    printf("\n=== Testing %s Storage ===\n", storage_name);

    D_storage *storage = funcs->create();

    // Test 1: Create and insert departments
    printf("Test 1: Creating and inserting departments...\n");
    String id1, id2, id3;
    create_str(&id1, "DEP1");
    create_str(&id2, "DEP2");
    create_str(&id3, "DEP3");

    Department* dep1 = create_department(id1, BINARY, 5, 0.8f);
    Department* dep2 = create_department(id2, TREAP, 3, 0.7f);
    Department* dep3 = create_department(id3, FIBONACCI, 4, 0.6f);

    funcs->insert(storage, dep1);
    funcs->insert(storage, dep2);
    funcs->insert(storage, dep3);

    // Test 2: Retrieve departments
    printf("\nTest 2: Retrieving departments...\n");
    Department *result;

    if (funcs->get(storage, id1, &result) == 1) {
        printf("Found DEP1: operators=%d\n", result->total_operators);
    } else {
        printf("DEP1 not found!\n");
    }

    if (funcs->get(storage, id2, &result) == 1) {
        printf("Found DEP2: operators=%d\n", result->total_operators);
    } else {
        printf("DEP2 not found!\n");
    }

    // Test 3: Try to get non-existent department
    printf("\nTest 3: Testing non-existent department...\n");
    String invalid_id;
    create_str(&invalid_id, "INVALID");
    if (funcs->get(storage, invalid_id, &result) == 0) {
        printf("Correctly reported non-existent department\n");
    } else {
        printf("Incorrectly found non-existent department!\n");
    }

    // Cleanup
    destroy_str(&id1);
    destroy_str(&id2);
    destroy_str(&id3);
    destroy_str(&invalid_id);
    funcs->destroy(storage);
}

void test_overload_heap() {
    printf("\n=== Testing Overload Binary Heap ===\n");

    OverloadBinaryHeap* heap = create_overload_binary_heap();

    // Test 1: Insert departments with different loads
    printf("Test 1: Inserting departments with different loads\n");
    String id1, id2, id3;
    create_str(&id1, "DEP1");
    create_str(&id2, "DEP2");
    create_str(&id3, "DEP3");

    Department dep1 = {.id = id1, .occupied_operators = 4, .total_operators = 5}; // Load: 0.8
    Department dep2 = {.id = id2, .occupied_operators = 1, .total_operators = 5}; // Load: 0.2
    Department dep3 = {.id = id3, .occupied_operators = 3, .total_operators = 5}; // Load: 0.6

    insert_overload_binary_heap(heap, dep1);
    insert_overload_binary_heap(heap, dep2);
    insert_overload_binary_heap(heap, dep3);

    // Test 2: Extract minimum overload
    printf("\nTest 2: Extracting departments by minimum load\n");
    String result;
    while (extract_min_overload_binary_heap(heap, &result) == 0) {
        printf("Extracted department: %s\n", result.val);
        destroy_str(&result);
    }

    // Cleanup
    destroy_str(&id1);
    destroy_str(&id2);
    destroy_str(&id3);
    destroy_overload_binary_heap(heap);
}

int main() {
//    printf("Starting comprehensive storage tests...\n");
//
//    const char* STORAGE_NAMES[] = {
//            "BST",
//            "Dynamic Array",
//            "HashSet",
//            "Trie"
//    };
//
//    const int NUM_STORAGES = sizeof(STORAGE_NAMES) / sizeof(STORAGE_NAMES[0]);
//
//    for (int i = 0; i < NUM_STORAGES; i++) {
//        test_storage(&STORAGE_IMPLEMENTATIONS[i], STORAGE_NAMES[i]);
//    }
////    test_storage(&STORAGE_IMPLEMENTATIONS[0], STORAGE_NAMES[0]);
////    test_storage(&STORAGE_IMPLEMENTATIONS[1], STORAGE_NAMES[1]);
////    test_storage(&STORAGE_IMPLEMENTATIONS[2], STORAGE_NAMES[2]);
////    test_storage(&STORAGE_IMPLEMENTATIONS[3], STORAGE_NAMES[3]);
//
//    printf("\nAll storage tests completed.\n");

    test_overload_heap();

//    TrieNode* root = create_trie_node('\0');
//
//    // Create test departments
//    String id1, id2, id3, id4, id5;
//    create_str(&id1, "DEP1");
//    create_str(&id2, "DEP2");
//    create_str(&id3, "DOG");
//    create_str(&id4, "DOOR");
//    create_str(&id5, "DORITOS");
//
//
//    Department* dep1 = create_department(id1, BINARY, 5, 0.8f);
//    Department* dep2 = create_department(id2, BINARY, 3, 0.7f);
//    Department* dep3 = create_department(id3, BINARY, 3, 0.7f);
//    Department* dep4 = create_department(id4, BINARY, 3, 0.7f);
//    Department* dep5 = create_department(id5, BINARY, 3, 0.7f);
//
//    insert_department_trie_node(root, dep1);
//    insert_department_trie_node(root, dep2);
//    insert_department_trie_node(root, dep3);
//    insert_department_trie_node(root, dep4);
//    insert_department_trie_node(root, dep5);

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
