#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include "../../utility/error_handler.h"
#include "../../utility/overio.h"
#include "../task4/mystring.h"

#include <stdio.h>
#include <math.h>

typedef struct Liver {
    String surname;
    String name;
    String patronymic;
    String birthdate;
    char sex;
    float mean_salary;
} Liver;

typedef struct LiverList {
    Liver val;
    struct LiverList *next;
} LiverList;

typedef struct Time {
    int day;
    int month;
    int year;
} Time;

typedef enum Command {
    HELP,
    ADD,
    REMOVE,
    EDIT,
    SEARCH,
    CHANGE_EXPORT_PATH,
    EXPORT,
    UNDO
} Command;

typedef enum DialogFSM {
    COMMAND_WAIT,
    COMMAND_HANDLE
} DialogFSM;

typedef enum SearchCriteria {
    SURNAME,
    NAME,
    PATRONYMIC,
    BIRTHDATE,
    SEX,
    SALARY
} SearchCriteria;

typedef union SearchParameter {
    String str;
    char sex;
    float salary;
} SearchParameter;

typedef struct Change {
    Command cmd;
    Liver *old;
    Liver *changed;
} Change;

typedef struct UndoStack {
    Change *val;
    unsigned int length;
    unsigned int capacity;
} UndoStack;


// Linked LiverList
LiverList* create_node(Liver val);
int prepend_list(LiverList **list, Liver val);
int append_list(LiverList **list, Liver val);
int insert_list_condition(LiverList **list, Liver val, int (*cmp)(const void*, const void*));
int delete_node(LiverList **list, LiverList *addr);
int copy_list(LiverList **dst, LiverList *src);
void destroy_list(LiverList **list);
void destroy_liver(Liver *liver);
int copy_liver(Liver *dst, const Liver *src);
int find_liver(LiverList **livers, Liver val, LiverList **result);
int liver_search(LiverList **livers, SearchCriteria criteria, SearchParameter param, LiverList **result);
void write_livers(FILE *out, LiverList *list);

int compare_age(const void *liver1, const void *liver2);

int parse_time(const String *str, Time *time);
int parse_time_arr(const Array *str, Time *time);


// Dialog
int dialog_manager(FILE *in);
int wait_command(Command *result);
int handle_command(Command cmd, LiverList **livers, Array *export_path, UndoStack *undoStack);
void cmd_description(Command cmd);
int wait_param(Command cmd, int *param);
int wait_search_param(SearchParameter *searchParam, SearchCriteria criteria);

void help_cmd();

int check_latin_letters(Array a);
int add_liver(LiverList **list, UndoStack *undoStack);
int delete_liver(LiverList **list, SearchCriteria criteria, SearchParameter parameter, UndoStack *undoStack);
int edit_liver(LiverList **list, SearchCriteria criteria, SearchParameter parameter, UndoStack *undoStack);
int read_livers_file(FILE* in, LiverList **list);
int change_export_path(Array *initial_path);
int undo_cmd(LiverList **list, UndoStack *stack);


// Undo stack
int create_stack(UndoStack *stack);
int push_stack(UndoStack *stack, Change change);
int resize_stack(UndoStack *stack, int size_delta);
Change* pop_stack(UndoStack *stack);
void destroy_stack(UndoStack *stack);


#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
