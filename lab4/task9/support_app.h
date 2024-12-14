#pragma once

#ifndef FUNDAMENTAL_ALGORITHMS_SUPPORT_APP_H
#define FUNDAMENTAL_ALGORITHMS_SUPPORT_APP_H

#include "../../utility/overio.h"

#include "main.h"

typedef struct SupportSystem {
    D_storage *departments;
    dept_functions storage_funcs;

    OverloadBinaryHeap *load_heap;
    Department **department_array;

    Time startModelTime;
    Time stopModelTime;

    Time currentModelTime;

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

void increment_minutes(Time *time, int minutes);

int ISO8601_to_Time(const char *input, Time *res);

double time_to_jdn(const Time *t);

long long time_difference_minutes(const Time *t1, const Time *t2);

int compare_time(const void *a, const void *b);

Ticket *create_ticket(Time time, int priority, String dept_id, String text_content);

Department *create_department(String id, HeapType heap_type, int total_operators, float overload_coefficient);

int compare_tickets(const void *t1, const void *t2);

int read_config_file(const char *filename, SupportSystem *result);

int read_tickets_from_file(SupportSystem *system, const char *filename);

int distribute_tickets_inside_department(Department *department, int minTicketTime, int maxTicketTime);

int first_distribution_all_tickets(SupportSystem *system);

int bleed_remaining_time(SupportSystem *system);

int redistribute_tickets(SupportSystem *system);

int check_for_updates_tickets(SupportSystem *system);

void destroy_system(SupportSystem *system);

int clear_log_file();

void log_event(const char* event_type, const char* description);

void log_new_request(const Ticket* ticket, const Department* dept);

void log_request_handling_started(const Ticket* ticket, const Operator* op);

void log_request_handling_finished(const Ticket* ticket, const Operator* op, int duration);

void log_department_overloaded(const Ticket* ticket, const Department* overloaded_dept, const Department* target_dept);

#endif //FUNDAMENTAL_ALGORITHMS_SUPPORT_APP_H
