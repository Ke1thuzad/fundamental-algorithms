#include "support_app.h"

int is_leap_year(int year) {
    if (year % 400 == 0)
        return 1;
    if (year % 100 == 0)
        return 0;
    if (year % 4 == 0)
        return 1;
    return 0;
}

int days_in_month(int month, int year) {
    if (month < 1 || month > 12)
        return 0;
    if (month == 2)
        return is_leap_year(year) ? 29 : 28;
    if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    return 31;
}

void increment_minutes(Time *time, int minutes) {
    time->minute += minutes;
    int extra_hours = time->minute / 60;
    time->minute %= 60;
    time->hour += extra_hours;
    int extra_days = time->hour / 24;
    time->hour %= 24;
    time->day += extra_days;

    while (time->day > days_in_month(time->month, time->year)) {
        time->day -= days_in_month(time->month, time->year);
        time->month++;
        if (time->month > 12) {
            time->month = 1;
            time->year++;
        }
    }
}

int ISO8601_to_Time(const char *input, Time *res) {
    if (input == NULL || res == NULL)
        return 0;

    if (sscanf(input, "%4d-%2d-%2dT%2d:%2d:%2d",
               &res->year, &res->month, &res->day,
               &res->hour, &res->minute, &res->second) != 6)
        return 0;

    if (res->month < 1 || res->month > 12)
        return 0;

    int days = days_in_month(res->month, res->year);
    if (days == 0 || res->day < 1 || res->day > days)
        return 0;

    if (res->hour < 0 || res->hour > 23)
        return 0;

    if (res->minute < 0 || res->minute > 59)
        return 0;

    if (res->second < 0 || res->second > 59)
        return 0;

    return 1;
}

double time_to_jdn(const Time *t) {
    int y = t->year;
    int m = t->month;
    int d = t->day;

    if (m <= 2) {
        y -= 1;
        m += 12;
    }

    double jdn = (1461 * (y + 4800)) / 4.0
                 + (367 * (m - 2)) / 12.0
                 - (3 * ((float) (y + 4900) / 100)) / 4.0
                 + d
                 - 32075;

    double time_fraction = (t->hour + t->minute / 60.0 + t->second / 3600.0) / 24.0;
    jdn += time_fraction;

    return jdn;
}

long long time_difference_minutes(const Time *t1, const Time *t2) {
    double jdn1 = time_to_jdn(t1);
    double jdn2 = time_to_jdn(t2);

    double diff_days = jdn1 - jdn2;
    long long diff_minutes = (long long) (diff_days * 1440.0);

    return diff_minutes;
}

int compare_time(const void *a, const void *b) {
    Time t1 = *((Time *) a);
    Time t2 = *((Time *) b);

    if (t1.year < t2.year) return -1;
    if (t1.year > t2.year) return 1;

    if (t1.month < t2.month) return -1;
    if (t1.month > t2.month) return 1;

    if (t1.day < t2.day) return -1;
    if (t1.day > t2.day) return 1;

    if (t1.hour < t2.hour) return -1;
    if (t1.hour > t2.hour) return 1;

    if (t1.minute < t2.minute) return -1;
    if (t1.minute > t2.minute) return 1;

    if (t1.second < t2.second) return -1;
    if (t1.second > t2.second) return 1;

    return 0;
}

Ticket *create_ticket(Time time, int priority, String dept_id, String text_content) {
    static int ticket_id_counter = 0;
    Ticket *ticket = (Ticket *) malloc(sizeof(Ticket));
    if (!ticket)
        return NULL;

    ticket->submit_time = time;
    ticket->priority = priority;
    ticket->ID = ticket_id_counter++;

    copy_newstr(&ticket->key, &dept_id);
    copy_newstr(&ticket->value, &text_content);

    return ticket;
}

void destroy_ticket(Ticket *ticket) {
    if (!ticket)
        return;

    destroy_str(&ticket->value);
    destroy_str(&ticket->key);
}

int read_config_file(const char *filename, SupportSystem *result) {
    FILE *in = fopen(filename, "r");
    if (!in)
        return throw_err(FILE_ERROR);

    HeapType heapType;
    StorageType storageType;

    Time modelStartTime;
    Time modelStopTime;

    int minTicketTime;
    int maxTicketTime;

    int departmentAmount;

    float overload_coefficient;

    int err;

    int chr;

    int cur_read;

    String *hTypeTemp = NULL, *sTypeTemp = NULL;

    char startTime[20], stopTime[20];

    cur_read = overfscanf(in, "%Sn\n%Sn\n%19s\n%19s\n%d\n%d\n%d", &hTypeTemp, &sTypeTemp, startTime, stopTime,
                          &minTicketTime, &maxTicketTime, &departmentAmount);

    if (cur_read == EOF || cur_read != 7 || !hTypeTemp || !sTypeTemp || minTicketTime < 1 || maxTicketTime < 1 ||
        departmentAmount < 1 || departmentAmount > 100 || !ISO8601_to_Time(startTime, &modelStartTime) ||
        !ISO8601_to_Time(stopTime, &modelStopTime) ||
        compare_time((const void *) &modelStartTime, (const void *) &modelStopTime) > 0) {
        if (hTypeTemp) {
            destroy_str(hTypeTemp);
            free(hTypeTemp);
        }
        if (sTypeTemp) {
            destroy_str(sTypeTemp);
            free(sTypeTemp);
        }

        return throw_err(INCORRECT_INPUT_DATA);
    }

    int operatorCounts[departmentAmount];

    for (int i = 0; i < departmentAmount; i++) {
        cur_read = fscanf(in, "%d", &operatorCounts[i]);
        if (cur_read != 1 || operatorCounts[i] < 10 || operatorCounts[i] > 50) {
            destroy_str(hTypeTemp);
            destroy_str(sTypeTemp);
            free(hTypeTemp);
            free(sTypeTemp);

            fclose(in);
            return throw_err(INCORRECT_INPUT_DATA);
        }
    }

    cur_read = fscanf(in, "%f", &overload_coefficient);
    if (cur_read != 1 || overload_coefficient < 1.0f) {
        destroy_str(hTypeTemp);
        free(hTypeTemp);
        destroy_str(sTypeTemp);
        free(sTypeTemp);
        fclose(in);
        return throw_err(INCORRECT_INPUT_DATA);
    }

    fclose(in);

    if (compare_str_and_cstr(*hTypeTemp, "BinaryHeap") == 0)
        heapType = BINARY;
    else if (compare_str_and_cstr(*hTypeTemp, "BinomialHeap") == 0)
        heapType = BINOMIAL;
    else if (compare_str_and_cstr(*hTypeTemp, "FibonacciHeap") == 0)
        heapType = FIBONACCI;
    else if (compare_str_and_cstr(*hTypeTemp, "SkewHeap") == 0)
        heapType = SKEW;
    else if (compare_str_and_cstr(*hTypeTemp, "LeftistHeap") == 0)
        heapType = LEFTIST;
    else if (compare_str_and_cstr(*hTypeTemp, "Treap") == 0)
        heapType = TREAP;
    else {
        destroy_str(hTypeTemp);
        free(hTypeTemp);
        destroy_str(sTypeTemp);
        free(sTypeTemp);
        return throw_err(INCORRECT_INPUT_DATA);
    }

    destroy_str(hTypeTemp);
    free(hTypeTemp);

    if (compare_str_and_cstr(*sTypeTemp, "HashSet") == 0)
        storageType = HASHSET;
    else if (compare_str_and_cstr(*sTypeTemp, "DynamicArray") == 0)
        storageType = DYNAMIC_ARRAY;
    else if (compare_str_and_cstr(*sTypeTemp, "BinarySearchTree") == 0)
        storageType = BST;
    else if (compare_str_and_cstr(*sTypeTemp, "Trie") == 0)
        storageType = TRIE;
    else {
        destroy_str(sTypeTemp);
        free(sTypeTemp);
        return throw_err(INCORRECT_INPUT_DATA);
    }

    destroy_str(sTypeTemp);
    free(sTypeTemp);

    dept_functions storage_funcs = STORAGE_IMPLEMENTATIONS[storageType];

    D_storage *storage = storage_funcs.create();
    if (!storage) {
        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    OverloadBinaryHeap *overloadBinaryHeap = create_overload_binary_heap();
    if (!overloadBinaryHeap) {
        storage_funcs.destroy(storage);
        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    result->department_array = (Department **) malloc(sizeof(Department *) * departmentAmount);

    for (int i = 1; i <= departmentAmount; ++i) {
        Array temp;
        err = create_arr(5, &temp);
        if (err) {
            destroy_overload_binary_heap(overloadBinaryHeap);
            storage_funcs.destroy(storage);
            return err;
        }

        value_to_arr(i, &temp);

        String dept_id;
        err = create_str(&dept_id, temp.val);
        destroy(&temp);
        if (err) {
            destroy_overload_binary_heap(overloadBinaryHeap);
            storage_funcs.destroy(storage);
            return err;
        }

        Department *dep = create_department(dept_id, heapType, operatorCounts[i - 1], overload_coefficient);
        destroy_str(&dept_id);
        if (!dep) {
            destroy_overload_binary_heap(overloadBinaryHeap);
            storage_funcs.destroy(storage);
            return throw_err(MEMORY_NOT_ALLOCATED);
        }

        result->department_array[i - 1] = dep;

        err = insert_overload_binary_heap(overloadBinaryHeap, *dep);
        if (err) {
            destroy_overload_binary_heap(overloadBinaryHeap);
            storage_funcs.destroy(storage);
            return err;
        }

        err = storage_funcs.insert(storage, dep);
        if (err) {
            destroy_overload_binary_heap(overloadBinaryHeap);
            storage_funcs.destroy(storage);
            return err;
        }
    }

    result->departments = storage;
    result->storage_funcs = STORAGE_IMPLEMENTATIONS[storageType];
    result->minTicketTime = minTicketTime;
    result->maxTicketTime = maxTicketTime;
    result->startModelTime = modelStartTime;
    result->stopModelTime = modelStopTime;
    result->overload_coefficient = overload_coefficient;
    result->load_heap = overloadBinaryHeap;

    return 0;
}

int read_tickets_from_file(SupportSystem *system, const char *filename) {
    if (!system || !filename)
        return throw_err(INCORRECT_ARGUMENTS);

    FILE *in = fopen(filename, "r");
    if (!in)
        return throw_err(FILE_ERROR);

    int ch, err, cur_read;

    do {
        char isoTime[20] = "";
        int priority;
        String *id = NULL;
        Time ticketTime;

        cur_read = overfscanf(in, "%19s %d %Sn", isoTime, &priority, &id);
        if (cur_read == EOF)
            break;
        if (cur_read != 3 || !id || priority < 0 || priority > system->max_priority ||
            !ISO8601_to_Time(isoTime, &ticketTime)) {
            if (id) {
                destroy_str(id);
                free(id);
            }
            fclose(in);
            return throw_err(INCORRECT_INPUT_DATA);
        }

        String text_content;
        err = create_str(&text_content, "");
        if (err) {
            destroy_str(id);
            free(id);
            fclose(in);
            return err;
        }

        err = seek_char(&in, &ch);
        if (err || ch == EOF || ch != '"') {
            destroy_str(id);
            free(id);
            destroy_str(&text_content);
            fclose(in);
            return throw_err(INCORRECT_INPUT_DATA);
        }

        while ((ch = fgetc(in)) > 0 && ch != '"') {
            err = append_str(&text_content, (char) ch);
            if (err) {
                destroy_str(id);
                free(id);
                destroy_str(&text_content);
                fclose(in);
                return err;
            }
        }

        if (ch <= 0) {
            destroy_str(id);
            free(id);
            destroy_str(&text_content);
            fclose(in);
            return throw_err(INCORRECT_INPUT_DATA);
        }

        Ticket *ticket = create_ticket(ticketTime, priority, *id, text_content);
        destroy_str(id);
        free(id);
        destroy_str(&text_content);
        if (!ticket) {
            fclose(in);
            return throw_err(MEMORY_NOT_ALLOCATED);
        }

        if (time_difference_minutes(&system->stopModelTime, &ticketTime) < 0) {
            destroy_ticket(ticket);
            free(ticket);
            continue;
        }

        if (time_difference_minutes(&system->startModelTime, &ticketTime) < 0) {
            if (system->remaining_ticket_amount + 1 >= system->remaining_ticket_capacity) {
                if (system->remaining_ticket_capacity == 0) system->remaining_ticket_capacity = 1;
                Ticket **new_tickets = (Ticket **) realloc(system->not_distributed_tickets,
                                                           sizeof(Ticket *) * (system->remaining_ticket_capacity *= 2));
                if (!new_tickets) {
                    fclose(in);
                    return throw_err(MEMORY_NOT_ALLOCATED);
                }

                system->not_distributed_tickets = new_tickets;
            }

            system->not_distributed_tickets[system->remaining_ticket_amount++] = ticket;
        } else {
            Department *department;
            err = system->storage_funcs.get(system->departments, ticket->key, &department);
            if (err != 1) {
                destroy_ticket(ticket);
                fclose(in);
                return err;
            }

            log_new_request(ticket, department);

            err = department->heap_funcs.insert(department->priority_queue, *ticket);
            destroy_ticket(ticket);
            free(ticket);
            if (err) {
                fclose(in);
                return err;
            }
        }
    } while (1);

    fclose(in);

    return 0;
}

int distribute_tickets_inside_department(Department *department, int minTicketTime, int maxTicketTime) {
    if (!department)
        return throw_err(INCORRECT_ARGUMENTS);

    int free_operators = department->total_operators - department->occupied_operators;
    int err;

    for (int i = 0; i < free_operators; ++i) {
        Ticket *extracted = (Ticket *) malloc(sizeof(Ticket));
        if (!extracted) {
            return throw_err(MEMORY_NOT_ALLOCATED);
        }

        err = department->heap_funcs.extract_max(department->priority_queue, extracted);
        if (err == OUT_OF_BOUNDS) {
            free(extracted);
            break;
        } else if (err) {
            destroy_ticket(extracted);
            free(extracted);
            return err;
        }

        department->occupied_operators++;

        for (int j = 0; j < department->total_operators; ++j) {
            Operator *cur_op = &department->operators[j];

            if (!cur_op->is_occupied) {
                cur_op->is_occupied = 1;
                cur_op->current_ticket = extracted;
                cur_op->initial_time = minTicketTime + rand() % (maxTicketTime - minTicketTime);
                cur_op->remaining_time = cur_op->initial_time;
                log_request_handling_started(cur_op->current_ticket, cur_op);
                break;
            }
        }
    }

    return 0;
}

int first_distribution_all_tickets(SupportSystem *system) {
    Department *department;
    int err;
    err = system->storage_funcs.get(system->departments, get_min_overload_binary_heap(system->load_heap), &department);
    if (err != 1)
        return err;

    while (1) {
        err = distribute_tickets_inside_department(department, system->minTicketTime, system->maxTicketTime);
        if (err)
            return err;

        float cur_load = get_department_load(*department);

        err = change_key_overload_binary_heap(system->load_heap, department->id, cur_load);
        if (err != 1)
            return err;

        Department *next_dept;

        err = system->storage_funcs.get(system->departments, get_min_overload_binary_heap(system->load_heap),
                                        &next_dept);
        if (err != 1)
            return err;

        if (cur_load > department->overload_coefficient) {
            Ticket ticket = department->heap_funcs.get_max_priority(department->priority_queue);

            log_department_overloaded(&ticket, department, next_dept);

            if (next_dept != department) {
                Q_queue *new = department->heap_funcs.create_heap();
                if (!new)
                    return throw_err(MEMORY_NOT_ALLOCATED);

                err = department->heap_funcs.merge_with_copy(next_dept->priority_queue, department->priority_queue,
                                                             new);
                if (err) {
                    department->heap_funcs.destroy(new);
                    return err;
                }

                department->heap_funcs.destroy(department->priority_queue);
                next_dept->heap_funcs.destroy(next_dept->priority_queue);

                department->priority_queue = department->heap_funcs.create_heap();
                if (!department->priority_queue) {
                    department->heap_funcs.destroy(new);
                    return throw_err(MEMORY_NOT_ALLOCATED);
                }

                next_dept->priority_queue = new;
            }
        }

        if (department == next_dept)
            break;

        department = next_dept;
    }

    return 0;
}

int bleed_remaining_time(SupportSystem *system) {
    int err;
    for (int i = 0; i < system->load_heap->size; ++i) {
        Department *cur_dep = system->department_array[i];
        int counter = 0;

        err = distribute_tickets_inside_department(cur_dep, system->minTicketTime, system->maxTicketTime);
        if (err)
            return err;

        for (int j = 0; j < cur_dep->total_operators; ++j) {
            Operator *cur_oper = &cur_dep->operators[j];

            if (!cur_oper->is_occupied)
                continue;

            counter++;

            cur_oper->remaining_time--;

            if (cur_oper->remaining_time <= 0) {
                log_request_handling_finished(cur_oper->current_ticket, cur_oper, cur_oper->initial_time);

                cur_oper->is_occupied = 0;
                if (cur_oper->current_ticket) {
                    destroy_ticket(cur_oper->current_ticket);
                    free(cur_oper->current_ticket);
                    cur_oper->current_ticket = NULL;
                }

                cur_dep->occupied_operators--;
            }

            if (counter >= cur_dep->occupied_operators)
                break;
        }
    }

    return 0;
}

int redistribute_tickets(SupportSystem *system) {
    int err;
    for (int i = 0; i < system->load_heap->size; ++i) {
        Department *cur_dep = system->department_array[i];
        float load = get_department_load(*cur_dep);

        if (load > cur_dep->overload_coefficient) {
            Department *best_dept;
            String best_id = get_min_overload_binary_heap(system->load_heap);
            err = system->storage_funcs.get(system->departments, best_id, &best_dept);
            if (err != 1 || best_dept == cur_dep || get_department_load(*best_dept) < best_dept->overload_coefficient)
                return 0;

            Ticket ticket = cur_dep->heap_funcs.get_max_priority(cur_dep->priority_queue);

            log_department_overloaded(&ticket, cur_dep, best_dept);

            Q_queue *new = best_dept->heap_funcs.create_heap();
            if (!new)
                return throw_err(MEMORY_NOT_ALLOCATED);

            err = best_dept->heap_funcs.merge_with_copy(best_dept->priority_queue, cur_dep->priority_queue, new);
            if (err) {
                cur_dep->heap_funcs.destroy(new);
                return err;
            }

            cur_dep->heap_funcs.destroy(cur_dep->priority_queue);
            best_dept->heap_funcs.destroy(best_dept->priority_queue);

            cur_dep->priority_queue = cur_dep->heap_funcs.create_heap();
            if (!cur_dep->priority_queue) {
                cur_dep->heap_funcs.destroy(new);
                return throw_err(MEMORY_NOT_ALLOCATED);
            }

            best_dept->priority_queue = new;

            // Обновляем нагрузку на отделы
            float new_load = get_department_load(*cur_dep);
            err = change_key_overload_binary_heap(system->load_heap, cur_dep->id, new_load);
            if (err != 1)
                return err;

            new_load = get_department_load(*best_dept);
            err = change_key_overload_binary_heap(system->load_heap, best_dept->id, new_load);
            if (err != 1)
                return err;
        }
    }

    return 0;
}

int check_for_updates_tickets(SupportSystem *system) {
    int err;
    for (int i = system->remaining_ticket_amount - 1; i >= 0; --i) {
        if (system->not_distributed_tickets[i] &&
            time_difference_minutes(&system->currentModelTime, &system->not_distributed_tickets[i]->submit_time) < 0)
            break;

        String dept_id = system->not_distributed_tickets[i]->key;
        Department *dept;
        err = system->storage_funcs.get(system->departments, dept_id, &dept);
        if (err != 1)
            return err;

        float load = get_department_load(*dept);
        if (load >= dept->overload_coefficient) {
            Department *best;
            String best_id = get_min_overload_binary_heap(system->load_heap);
            err = system->storage_funcs.get(system->departments, best_id, &best);
            if (err != 1)
                return err;

            log_new_request(system->not_distributed_tickets[i], best);

            err = best->heap_funcs.insert(best->priority_queue, *system->not_distributed_tickets[i]);
            system->remaining_ticket_amount--;
            destroy_ticket(system->not_distributed_tickets[i]);
            free(system->not_distributed_tickets[i]);
            if (err)
                return err;
        } else {
            log_new_request(system->not_distributed_tickets[i], dept);

            err = dept->heap_funcs.insert(dept->priority_queue, *system->not_distributed_tickets[i]);
            system->remaining_ticket_amount--;
            destroy_ticket(system->not_distributed_tickets[i]);
            free(system->not_distributed_tickets[i]);
        }
    }

    return 0;
}

void destroy_system(SupportSystem *system) {
    for (int i = 0; i < system->remaining_ticket_amount; ++i) {
        destroy_ticket(system->not_distributed_tickets[i]);
        free(system->not_distributed_tickets[i]);
    }

    free(system->not_distributed_tickets);

    system->storage_funcs.destroy(system->departments);

    free(system->department_array);

    destroy_overload_binary_heap(system->load_heap);
}

int compare_tickets(const void *t1, const void *t2) {
    Ticket *ticketA = *(Ticket **) t1;
    Ticket *ticketB = *(Ticket **) t2;

    int cmp_time = -compare_time(&ticketA->submit_time, &ticketB->submit_time);
    if (cmp_time != 0)
        return cmp_time;

    return ticketB->priority - ticketA->priority;
}

int clear_log_file() {
    FILE *log_file = fopen("log.txt", "w");
    if (!log_file) {
        return throw_err(FILE_ERROR);
    }
    fclose(log_file);

    return 0;
}

void log_event(const char *event_type, const char *description) {
    FILE *log_file = fopen("log.txt", "a");
    if (!log_file) {
        fprintf(stderr, "Error opening log file.\n");
        return;
    }
    fprintf(log_file, "[%s]: %s\n", event_type, description);
    fclose(log_file);
}

void log_new_request(const Ticket *ticket, const Department *dept) {
    char description[4096];
    snprintf(description, sizeof(description), "NEW_REQUEST: Ticket ID: %d, Department ID: %s", ticket->ID,
             dept->id.val);
    log_event("NEW_REQUEST", description);
}

void log_request_handling_started(const Ticket *ticket, const Operator *op) {
    char description[4096];
    snprintf(description, sizeof(description), "REQUEST_HANDLING_STARTED: Ticket ID: %d, Operator: %s", ticket->ID,
             op->name.val);
    log_event("REQUEST_HANDLING_STARTED", description);
}

void log_request_handling_finished(const Ticket *ticket, const Operator *op, int duration) {
    char description[4096];
    snprintf(description, sizeof(description),
             "REQUEST_HANDLING_FINISHED: Ticket ID: %d, Duration: %d minutes, Operator: %s", ticket->ID, duration,
             op->name.val);
    log_event("REQUEST_HANDLING_FINISHED", description);
}

void log_department_overloaded(const Ticket *ticket, const Department *overloaded_dept, const Department *target_dept) {
    char description[4096];
    snprintf(description, sizeof(description),
             "DEPARTMENT_OVERLOADED: Ticket ID: %d, Overloaded Department ID: %s, Transferred to Department ID: %s",
             ticket->ID, overloaded_dept->id.val, target_dept->id.val);
    log_event("DEPARTMENT_OVERLOADED", description);
}