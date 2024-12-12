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

// https://en.wikipedia.org/wiki/Julian_day#Finding_Julian_date_given_Julian_day_number_and_time_of_day
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

    if (t1.year != t2.year) return t1.year - t2.year;

    if (t1.month != t2.month) return t1.month - t2.month;

    if (t1.day != t2.day) return t1.day - t2.day;

    if (t1.hour != t2.hour) return t1.hour - t2.hour;

    if (t1.minute != t2.minute) return t1.minute - t2.minute;

    return t1.second - t2.second;
}

Ticket *create_ticket(Time time, int priority, String dept_id, String text_content) {
    Ticket *ticket = (Ticket *) malloc(sizeof(Ticket));
    if (!ticket)
        return NULL;

    ticket->submit_time = time;
    ticket->priority = priority;

    copy_newstr(&ticket->key, &dept_id);
    copy_newstr(&ticket->value, &text_content);

    return ticket;
}

void destroy_ticket(Ticket *ticket) {
    destroy_str(&ticket->value);
    destroy_str(&ticket->key);
}

int read_config_file(const char *filename, SupportSystem *result) {
    FILE *in = fopen(filename, "r");
    if (!in)
        return throw_err(FILE_ERROR);

    // Initialization Start
    HeapType heapType;
    StorageType storageType;

    Time modelStartTime;
    Time modelStopTime;

    int minTicketTime;
    int maxTicketTime;

    int departmentAmount;

    float overload_coefficient;
    // Initialization Stop

    int err;

    int chr;

    err = seek_char(&in, &chr);
    if (err) {
        fclose(in);
        return err;
    }

    if (chr == EOF) {
        fclose(in);
        return throw_err(INCORRECT_INPUT_DATA);
    }

    int cur_read;

    String *hTypeTemp = NULL, *sTypeTemp = NULL;

    char startTime[20], stopTime[20];

    cur_read = overfscanf(in, "%Sn\n%Sn\n%19s\n%19s\n%d\n%d\n%d", hTypeTemp, sTypeTemp, startTime, stopTime,
                          &minTicketTime, &maxTicketTime, &departmentAmount);

    int operatorCounts[departmentAmount];

    if (cur_read == EOF || cur_read != 7 || !hTypeTemp || !sTypeTemp || minTicketTime < 1 || maxTicketTime < 1 ||
        departmentAmount < 1 || departmentAmount > 100 || !ISO8601_to_Time(startTime, &modelStartTime) ||
        !ISO8601_to_Time(stopTime, &modelStopTime) ||
        compare_time((const void *) &modelStartTime, (const void *) &modelStopTime) > 0) {
        if (hTypeTemp)
            destroy_str(hTypeTemp);
        if (sTypeTemp)
            destroy_str(sTypeTemp);

        return throw_err(INCORRECT_INPUT_DATA);
    }

    for (int i = 0; i < departmentAmount; i++) {
        cur_read = fscanf(in, "%d", &operatorCounts[i]);
        if (cur_read != 1 || operatorCounts[i] < 10 || operatorCounts[i] > 50) {
            destroy_str(hTypeTemp);
            destroy_str(sTypeTemp);

            fclose(in);
            return throw_err(INCORRECT_INPUT_DATA);
        }
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
        destroy_str(sTypeTemp);
        return throw_err(INCORRECT_INPUT_DATA);
    }

    destroy_str(hTypeTemp);

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
        return throw_err(INCORRECT_INPUT_DATA);
    }

    destroy_str(sTypeTemp);

    cur_read = fscanf(in, "%f", &overload_coefficient);
    if (cur_read != 1 || overload_coefficient < 1.0f) {
        return throw_err(INCORRECT_INPUT_DATA);
    }

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

    result->department_array = (Department **) malloc(sizeof(Department*) * departmentAmount);

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

        insert_overload_binary_heap(overloadBinaryHeap, *dep);
        storage_funcs.insert(storage, dep);
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

        cur_read = overfscanf(in, "%19s %d %Sn", isoTime, &priority, id);
        if (cur_read == EOF)
            break;
        if (cur_read != 3 || !id || priority < 0 || priority > system->max_priority ||
            !ISO8601_to_Time(isoTime, &ticketTime)) {
            if (id)
                destroy_str(id);
            fclose(in);
            return throw_err(INCORRECT_INPUT_DATA);
        }

        String text_content;
        err = create_str(&text_content, "");
        if (err) {
            destroy_str(id);
            fclose(in);
            return err;
        }

        err = seek_char(&in, &ch);
        if (err || ch == EOF || ch != '"') {
            destroy_str(id);
            destroy_str(&text_content);
            fclose(in);
            return throw_err(INCORRECT_INPUT_DATA);
        }

        while ((ch = fgetc(in)) > 0 && ch != '"') {
            err = append_str(&text_content, (char) ch);
            if (err) {
                destroy_str(id);
                destroy_str(&text_content);
                fclose(in);
                return err;
            }
        }

        if (ch <= 0) {
            destroy_str(id);
            destroy_str(&text_content);
            fclose(in);
            return throw_err(INCORRECT_INPUT_DATA);
        }

        Ticket *ticket = create_ticket(ticketTime, priority, *id, text_content);
        destroy_str(id);
        destroy_str(&text_content);
        if (!ticket) {
            fclose(in);
            return throw_err(MEMORY_NOT_ALLOCATED);
        }

        if (time_difference_minutes(&system->stopModelTime, &ticketTime) < 0) {
            continue;
        }

        if (time_difference_minutes(&system->startModelTime, &ticketTime) > 0) {
            if (system->remaining_ticket_amount + 1 >= system->remaining_ticket_capacity) {
                Ticket **new_tickets = (Ticket **) realloc(system->not_distributed_tickets,
                                                           sizeof(Ticket *) * (system->remaining_ticket_capacity *= 2));
                if (!new_tickets) {
                    destroy_ticket(ticket);
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

            err = department->heap_funcs.insert(department->priority_queue, *ticket);
            destroy_ticket(ticket);
            if (err) {
                fclose(in);
                return err;
            }

//            change_key_overload_binary_heap(system->load_heap, department->id, get_department_load(*department));
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
        Ticket *extracted = NULL;
        err = department->heap_funcs.extract_max(department->priority_queue, extracted);
        if (err == OUT_OF_BOUNDS || !extracted)
            break;
        else if (err) {
            destroy_ticket(extracted);
            return err;
        }

        department->occupied_operators++;

        for (int j = 0; j < department->total_operators; ++j) {
            Operator *cur_op = &department->operators[j];

            if (!cur_op->is_occupied) {
                cur_op->is_occupied = 1;
                cur_op->current_ticket = extracted;
                cur_op->remaining_time = minTicketTime + rand() % (maxTicketTime - minTicketTime);
                // TODO: Log requests.
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
    if (err)
        return err;

    while (1) {
        err = distribute_tickets_inside_department(department, system->minTicketTime, system->maxTicketTime);
        if (err)
            return err;

        float cur_load = get_department_load(*department);

        err = change_key_overload_binary_heap(system->load_heap, department->id, cur_load);
        if (err)
            return err;

        // TODO: Check overload and log it.

        Department *next_dept;

        err = system->storage_funcs.get(system->departments, get_min_overload_binary_heap(system->load_heap), &next_dept);
        if (err)
            return err;

        // TODO: Check overload and log it.
        if (cur_load > department->overload_coefficient) {
            Q_queue *new = department->heap_funcs.create_heap();
            if (!new)
                return throw_err(MEMORY_NOT_ALLOCATED);

            err = department->heap_funcs.merge(next_dept->priority_queue, department->priority_queue, new);
            if (err) {
                department->heap_funcs.destroy(new);
                return err;
            }

            department->heap_funcs.destroy(department->priority_queue);
            next_dept->heap_funcs.destroy(next_dept->priority_queue);

            next_dept->priority_queue = new;
        }

        department = next_dept;

        if (get_department_load(*department) > 0)
            break;
    }

    return 0;
}

int bleed_remaining_time(SupportSystem *system) {
    for (int i = 0; i < system->load_heap->size; ++i) {
        Department *cur_dep = system->department_array[i];
        int counter = 0;
        for (int j = 0; j < cur_dep->total_operators; ++j) {
            Operator *cur_oper = &cur_dep->operators[j];

            if (!cur_oper->is_occupied) {
                continue;
            }

            counter++;

            cur_oper->remaining_time--;

            if (cur_oper->remaining_time <= 0) {
                cur_oper->is_occupied = 0;
                destroy_ticket(cur_oper->current_ticket);  // TODO: Log it.
                cur_dep->occupied_operators--;
            }

            if (counter >= cur_dep->occupied_operators)
                break;
        }
    }

    return 0;
}
