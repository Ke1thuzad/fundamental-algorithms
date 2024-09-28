#include <math.h>
#include "main.h"

char *stringcopy(char *dst, const char *src) {
    char *dstaddr = dst;
    while(*dst++ = *src++);
    return dstaddr;
}

void process_files(char *in, char *out, handler func) {
    FILE *in_stream = fopen(in, "r");
    if (!in_stream) {
        exit(FILE_ERROR);
    }

    func(in_stream, out);
    fclose(in_stream);
}

void to_base16(int x, char *result, int size) {
    int i = size - 1;
    char letters[16] = "0123456789ABCDEF";

    while (x > 0) {
        result[i--] = letters[x % 16];
        x /= 16;
    }
}

int is_num(int x) {
    return x >= '0' && x <= '9';
}

int is_letter(int x) {
    return x >= 'A' && x <= 'Z' || x >= 'a' && x <= 'z';
}

void handler_option_d(FILE *in_stream, char *out_filename) {
    FILE *out_stream = fopen(out_filename, "w");
    if (!out_stream) {
        exit(FILE_ERROR);
    }

    int cur;
    while (!feof(in_stream)) {
        cur = fgetc(in_stream);

        if (cur > 0 && !is_num(cur)) {
            fputc(cur, out_stream);
        }
    }

    fclose(out_stream);
}

void handler_option_i(FILE *in_stream, char *out_filename) {
    FILE *out_stream = fopen(out_filename, "w");
    if (!out_stream) {
        exit(FILE_ERROR);
    }
    int cur;
    unsigned int length = 0;

    while (!feof(in_stream)) {
        cur = fgetc(in_stream);
        if (is_letter(cur)) {
            length++;
        } else if (cur == '\n') {
            fprintf(out_stream, "This string contains %d latin letters.\n", length);
            length = 0;
        }
    }

    fclose(out_stream);
}

void handler_option_s(FILE *in_stream, char *out_filename) {
    FILE *out_stream = fopen(out_filename, "w");
    if (!out_stream) {
        exit(FILE_ERROR);
    }
    int cur;
    unsigned int length = 0;

    while (!feof(in_stream)) {
        cur = fgetc(in_stream);
        if (!(is_letter(cur) || is_num(cur) || cur == ' ') && cur != '\n') {
            length++;
        } else if (cur == '\n') {
            fprintf(out_stream, "This string contains %d characters, except letters, digits and whitespace.\n", length);
            length = 0;
        }
    }

    fclose(out_stream);
}

void handler_option_a(FILE *in_stream, char *out_filename) {
    FILE *out_stream = fopen(out_filename, "w");
    if (!out_stream) {
        exit(FILE_ERROR);
    }
    int cur;

    while (!feof(in_stream)) {
        cur = fgetc(in_stream);
        if (cur != EOF && !is_num(cur)) {
            int size = (int) (log2(cur) * 0.25) + 1;
            char result[size];
            to_base16(cur, result, size);
            fprintf(out_stream, "%s", result);
        }
    }

    fclose(out_stream);
}


