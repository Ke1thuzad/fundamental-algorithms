#include "department.h"

const dept_functions STORAGE_IMPLEMENTATIONS[] = {
        {   // BST Implementation
                .create = (D_storage *(*)()) create_department_bst,
                .insert = (int (*)(D_storage *, Department *)) insert_department_bstree,
                .get = (int (*)(D_storage *, String, Department **)) get_from_department_bstree,
                .destroy = (void (*)(D_storage *)) destroy_department_bstree
        },
        {   // Dynamic Array Implementation
                .create = (D_storage *(*)()) create_department_array,
                .insert = (int (*)(D_storage *, Department *)) insert_department_array,
                .get = (int (*)(D_storage *, String, Department **)) get_from_department_array,
                .destroy = (void (*)(D_storage *)) destroy_department_array
        },
        {   // HashSet Implementation
                .create = (D_storage *(*)()) create_standard_hash_table,
                .insert = (int (*)(D_storage *, Department *)) insert_hashnode,
                .get = (int (*)(D_storage *, String, Department **)) get_from_hashtable,
                .destroy = (void (*)(D_storage *)) destroy_hash_table
        },
        {   // Trie Implementation
                .create = (D_storage *(*)()) create_trie,
                .insert = (int (*)(D_storage *, Department *)) insert_department_trie_node,
                .get = (int (*)(D_storage *, String, Department **)) search_department_trie,
                .destroy = (void (*)(D_storage *)) destroy_trie
        }
};

char *generate_base52_string(int len) {
    char mapping[52] = {
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };
    char *buf = (char *) calloc(1, len + 1);
    if (!buf)
        return NULL;

    for (int i = 0; i < len; i++) {
        long index = rand() % 52;
        buf[i] = mapping[index];
    }
    buf[len] = '\0';
    return buf;
}

String *randomize_operator_name(Department *department) {
    char *str;
    int unique;
    do {
        str = generate_base52_string(16);
        if (!str)
            return NULL;
        unique = is_operator_name_unique(department, str);
        if (unique)
            free(str);
    } while (unique);

    String *result = (String *) malloc(sizeof(String));
    if (!result) {
        free(str);
        return NULL;
    }

    int err = create_str(result, str);
    free(str);
    if (err) {
        free(result);
        return NULL;
    }

    return result;
}

int is_operator_name_unique(Department *department, char *name) {
    for (int i = 0; i < department->total_operators; i++) {
        if (department->operators[i].name.val && compare_str_and_cstr(department->operators[i].name, name) == 0) {
            return 1;
        }
    }
    return 0;
}

Department *create_department(String id, HeapType heap_type, int total_operators, float overload_coefficient) {
    Department *new_department = (Department *) malloc(sizeof(Department));
    if (!new_department)
        return NULL;

    copy_newstr(&new_department->id, &id);

    new_department->heap_funcs = HEAP_IMPLEMENTATIONS[heap_type];
    new_department->priority_queue = new_department->heap_funcs.create_heap();

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

        String *random_name = randomize_operator_name(new_department);

        copy_newstr(&cur_op->name, random_name);

        destroy_str(random_name);
        free(random_name);
    }

    return new_department;
}

float get_department_load(Department department) {
    float total_tickets = (float) (department.occupied_operators +
                                   department.heap_funcs.get_size(department.priority_queue));
    return total_tickets / (float) department.total_operators;
}

void destroy_department(Department *department) {
    destroy_str(&department->id);

    if (department->priority_queue) {
        department->heap_funcs.destroy(department->priority_queue);
        department->priority_queue = NULL;
    }

    for (int i = 0; i < department->total_operators; ++i) {
        Operator *cur_op = &department->operators[i];

        destroy_str(&cur_op->name);
        if (cur_op->is_occupied && cur_op->current_ticket) {
            destroy_str(&cur_op->current_ticket->key);
            destroy_str(&cur_op->current_ticket->value);
            free(cur_op->current_ticket);
        }
    }

    free(department->operators);
}
