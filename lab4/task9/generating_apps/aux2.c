#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Time {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} Time;

int is_leap_year(int year) {
    if (year % 400 == 0) return 1;
    if (year % 100 == 0) return 0;
    if (year % 4 == 0) return 1;
    return 0;
}

int days_in_month(int month, int year) {
    if (month < 1 || month > 12) return 0;
    if (month == 2) return is_leap_year(year) ? 29 : 28;
    if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
    return 31;
}

int ISO8601_to_Time(const char *input, Time *res) {
    if (input == NULL || res == NULL) return 0;
    if (sscanf(input, "%4d-%2d-%2dT%2d:%2d:%2d",
               &res->year, &res->month, &res->day,
               &res->hour, &res->minute, &res->second) != 6) return 0;
    if (res->month < 1 || res->month > 12) return 0;
    int days = days_in_month(res->month, res->year);
    if (days == 0 || res->day < 1 || res->day > days) return 0;
    if (res->hour < 0 || res->hour > 23) return 0;
    if (res->minute < 0 || res->minute > 59) return 0;
    if (res->second < 0 || res->second > 59) return 0;
    return 1;
}

void generate_random_time(char* buffer, const char* min_time, const char* max_time) {
    Time min_parsed, max_parsed;
    if (!ISO8601_to_Time(min_time, &min_parsed) || !ISO8601_to_Time(max_time, &max_parsed)) {
        fprintf(stderr, "Invalid time format.\n");
        exit(1);
    }

    int year = min_parsed.year + rand() % (max_parsed.year - min_parsed.year + 1);

    int min_month = (year == min_parsed.year) ? min_parsed.month : 1;
    int max_month = (year == max_parsed.year) ? max_parsed.month : 12;
    int month = min_month + rand() % (max_month - min_month + 1);

    int min_day = (year == min_parsed.year && month == min_parsed.month) ? min_parsed.day : 1;
    int max_day = (year == max_parsed.year && month == max_parsed.month) ? max_parsed.day : days_in_month(month, year);
    int day = min_day + rand() % (max_day - min_day + 1);

    int hour = min_parsed.hour + rand() % (max_parsed.hour - min_parsed.hour + 1);
    int minute = min_parsed.minute + rand() % (max_parsed.minute - min_parsed.minute + 1);
    int second = min_parsed.second + rand() % (max_parsed.second - min_parsed.second + 1);

    sprintf(buffer, "%04d-%02d-%02dT%02d:%02d:%02d", year, month, day, hour, minute, second);
}

void generate_random_text(char* buffer, int max_length) {
    const char* words[] = {"help", "issue", "problem", "urgent", "support", "request", "error", "bug", "fix", "please"};
    int word_count = sizeof(words) / sizeof(words[0]);
    int length = 0;
    buffer[length++] = '"';
    while (length < max_length - 2) {
        const char* word = words[rand() % word_count];
        int word_len = strlen(word);
        if (length + word_len + 1 >= max_length - 2) break;
        strcpy(buffer + length, word);
        length += word_len;
        buffer[length++] = ' ';
    }
    buffer[length++] = '"';
    buffer[length] = '\0';
}

void generate_random_filename(char* buffer, int index) {
    sprintf(buffer, "ticket_file_%d.txt", index);
}

int main() {
    srand(time(NULL));

    const char* min_time = "2024-12-01T00:00:00";
    const char* max_time = "2024-12-13T23:59:59";

    int department_count = 10;
    int max_priority = 100;
    int file_count = 1 + rand() % 10;
    printf("Generating %d ticket files...\n", file_count);

    for (int i = 0; i < file_count; i++) {
        char filename[100];
        generate_random_filename(filename, i + 1);
        int ticket_count = 1 + rand() % 100;
        FILE* file = fopen(filename, "w");
        if (!file) {
            fprintf(stderr, "Error opening file: %s\n", filename);
            continue;
        }

        for (int j = 0; j < ticket_count; j++) {
            char time[20];
            generate_random_time(time, min_time, max_time);
            int priority = rand() % (max_priority + 1);
            int dept_id = 1 + rand() % department_count;
            char text[100];
            generate_random_text(text, sizeof(text));
            fprintf(file, "%s %d %d %s\n", time, priority, dept_id, text);
        }

        fclose(file);
        printf("Generated ticket file: %s with %d tickets\n", filename, ticket_count);
    }

    printf("All ticket files generated successfully.\n");
    return 0;
}