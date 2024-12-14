#include "main.h"

int main(int argc, char **argv) {
    if (argc < 3)
        return throw_err(INCORRECT_ARGUMENTS);

    int max_priority, err;

    err = clear_log_file();
    if (err)
        return err;

    srand(time(NULL));

    max_priority = (int) strtol(argv[1], NULL, 10);

    if (max_priority < 0)
        return throw_err(INCORRECT_ARGUMENTS);

    SupportSystem system = {.max_priority = max_priority};

    err = read_config_file(argv[2], &system);
    if (err)
        return err;

    for (int i = 3; i < argc; ++i) {
        err = read_tickets_from_file(&system, argv[i]);
        if (err) {
            destroy_system(&system);
            return err;
        }
    }

    qsort(system.not_distributed_tickets, system.remaining_ticket_amount, sizeof(Ticket *), compare_tickets);

    err = first_distribution_all_tickets(&system);
    if (err) {
        destroy_system(&system);
        return err;
    }

    system.currentModelTime = system.startModelTime;

    for (int i = 0; i < -time_difference_minutes(&system.startModelTime, &system.stopModelTime); ++i) {
        increment_minutes(&system.currentModelTime, 1);

        err = check_for_updates_tickets(&system);
        if (err) {
            destroy_system(&system);
            return err;
        }

        err = bleed_remaining_time(&system);
        if (err) {
            destroy_system(&system);
            return err;
        }

        err = redistribute_tickets(&system);
        if (err) {
            destroy_system(&system);
            return err;
        }
        if (i == 800) {
            int asa = 1;
        }
    }

    destroy_system(&system);

    return 0;
}
