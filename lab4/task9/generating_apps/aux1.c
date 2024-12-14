#include <stdio.h>
#include <string.h>

typedef struct Time {
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int second;
} Time;

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

void skip_to_nl(FILE *stream) {
    int ch = fgetc(stream);
    while (ch > 0 && ch != '\n') {
        ch = fgetc(stream);
    }
}

int validate_string(const char* input, const char* valid_options[], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(input, valid_options[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int read;

    printf("Configuration file creation. If string exceeds limit - it will be cut off\n");

    char filename[1001] = "";
    while (1) {
        printf("Please enter your config file name (max 1000 characters): ");
        read = scanf("%1000s", filename);
        if (read == 1) {
            break;
        } else {
            printf("Invalid input. Please try again.\n");
            skip_to_nl(stdin);
        }
    }
    skip_to_nl(stdin);

    const char* heap_types[] = {"BinaryHeap", "BinomialHeap", "FibonacciHeap", "SkewHeap", "LeftistHeap", "Treap"};
    char heaptype[14] = "";
    while (1) {
        printf("Enter heap type (BinaryHeap, BinomialHeap, FibonacciHeap, SkewHeap, LeftistHeap, Treap): ");
        read = scanf("%13s", heaptype);
        if (read == 1 && validate_string(heaptype, heap_types, 6)) {
            break;
        } else {
            printf("Invalid heap type. Please try again.\n");
            skip_to_nl(stdin);
        }
    }
    skip_to_nl(stdin);

    const char* storage_types[] = {"HashSet", "DynamicArray", "BinarySearchTree", "Trie"};
    char storage_type[17] = "";
    while (1) {
        printf("Enter storage type (HashSet, DynamicArray, BinarySearchTree, Trie): ");
        read = scanf("%16s", storage_type);
        if (read == 1 && validate_string(storage_type, storage_types, 4)) {
            break;
        } else {
            printf("Invalid storage type. Please try again.\n");
            skip_to_nl(stdin);
        }
    }
    skip_to_nl(stdin);

    char start_time[20] = "";
    while (1) {
        printf("Enter start time (YYYY-MM-DDTHH:MM:SS): ");
        read = scanf("%19s", start_time);
        Time temp_time;
        if (read == 1 && ISO8601_to_Time(start_time, &temp_time)) {
            break;
        } else {
            printf("Invalid start time. Please try again.\n");
            skip_to_nl(stdin);
        }
    }
    skip_to_nl(stdin);

    char stop_time[20] = "";
    while (1) {
        printf("Enter stop time (YYYY-MM-DDTHH:MM:SS): ");
        read = scanf("%19s", stop_time);
        Time temp_time;
        if (read == 1 && ISO8601_to_Time(stop_time, &temp_time)) {
            break;
        } else {
            printf("Invalid stop time. Please try again.\n");
            skip_to_nl(stdin);
        }
    }
    skip_to_nl(stdin);

    int min_process_time;
    while (1) {
        printf("Enter minimum ticket processing time (minutes): ");
        read = scanf("%d", &min_process_time);
        if (read == 1 && min_process_time >= 0) {
            break;
        } else {
            printf("Invalid input. Please try again.\n");
            skip_to_nl(stdin);
        }
    }
    skip_to_nl(stdin);

    int max_process_time;
    while (1) {
        printf("Enter maximum ticket processing time (minutes): ");
        read = scanf("%d", &max_process_time);
        if (read == 1 && max_process_time >= min_process_time) {
            break;
        } else {
            printf("Invalid input. Please try again.\n");
            skip_to_nl(stdin);
        }
    }
    skip_to_nl(stdin);

    int dept_amount;
    while (1) {
        printf("Enter department amount (1-100): ");
        read = scanf("%d", &dept_amount);
        if (read == 1 && dept_amount >= 1 && dept_amount <= 100) {
            break;
        } else {
            printf("Invalid input. Please try again.\n");
            skip_to_nl(stdin);
        }
    }
    skip_to_nl(stdin);

    float overload_coef;
    while (1) {
        printf("Enter overload coefficient (1.0 or higher): ");
        read = scanf("%f", &overload_coef);
        if (read == 1 && overload_coef >= 1.0) {
            break;
        } else {
            printf("Invalid input. Please try again.\n");
            skip_to_nl(stdin);
        }
    }
    skip_to_nl(stdin);

    FILE *out = fopen(filename, "w");
    if (!out) {
        printf("Error opening file.\n");
        return 1;
    }

    fprintf(out, "%s\n%s\n%s\n%s\n%d\n%d\n%d\n", heaptype, storage_type, start_time, stop_time, min_process_time, max_process_time, dept_amount);

    for (int i = 0; i < dept_amount; i++) {
        int operators;
        while (1) {
            printf("Enter number of operators for department №%d (10-50): ", i + 1);
            read = scanf("%d", &operators);
            if (read == 1 && operators >= 10 && operators <= 50) {
                break;
            } else {
                printf("Invalid input. Please try again.\n");
                skip_to_nl(stdin);
            }
        }
        fprintf(out, "%d ", operators);
    }

    fprintf(out, "\n%f\n", overload_coef);

    fclose(out);
    printf("Config file generated successfully: %s\n", filename);

    return 0;
}