#ifndef FUNDAMENTAL_ALGORITHMS_SUPPORT_APP_H
#define FUNDAMENTAL_ALGORITHMS_SUPPORT_APP_H

#include "../../utility/arrays/array.h"
#include "../../utility/overio.h"

#include "main.h"

typedef struct SupportSystem {
    D_storage *departments;
    dept_functions storage_funcs;

    OverloadBinaryHeap *load_heap;
    Department **department_array;

    Time startModelTime;
    Time stopModelTime;

    int minTicketTime;
    int maxTicketTime;

    int max_priority;
    float overload_coefficient;

    Ticket **not_distributed_tickets;
    int remaining_ticket_amount;
    int remaining_ticket_capacity;
} SupportSystem;

typedef enum LOG_CODES {
    NEW_REQUEST,
    REQUEST_HANDLING_STARTED,
    REQUEST_HANDLING_FINISHED,
    DEPARTMENT_OVERLOADED
} LOG_CODES;


int is_leap_year(int year);

int days_in_month(int month, int year);

int ISO8601_to_Time(const char *input, Time *res);

int compare_time(const void *a, const void *b);

Ticket *create_ticket(Time time, int priority, String dept_id, String text_content);

void destroy_ticket(Ticket *ticket);

int read_config_file(const char *filename, SupportSystem *result);

int read_tickets_from_file(SupportSystem *system, const char *filename);

int distribute_tickets_inside_department(Department *department, int minTicketTime, int maxTicketTime);

int first_distribution_all_tickets(SupportSystem *system);


//int log_event(SupportSystem *system, LOG_CODES code, Ticket *ticket);


#endif //FUNDAMENTAL_ALGORITHMS_SUPPORT_APP_H
