#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include "../../utility/error_handler.h"
#include "../../utility/arrays/array.h"
#include "../../utility/overio.h"
#include "mail.h"
#include "../task5/main.h"
#include "../task7/main.h"

#include <stdio.h>

typedef enum DialogFSM {
    COMMAND_WAIT,
    COMMAND_HANDLE,
    PARAMETER_WAIT
} DialogFSM;

typedef enum Command {
    HELP,
    ADD,
    REMOVE,
    PRINT,
    SEARCH
} Command;

int init_post(Post *post);
int dialog_manager();
int wait_command(Command *result);
int handle_command(Command cmd, Post *post);
int wait_param(Command cmd, int *param);
int wait_search_param(SearchParameter *searchParam, SearchCriteria criteria);

void cmd_description(Command cmd);
void help_cmd();
void print_cmd(Post post);
int add_mail_cmd(Post *post);

#endif //FUNDAMENTAL_ALGORITHMS_MAIN_H
