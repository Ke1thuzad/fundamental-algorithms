#include "main.h"

int calculator(FILE *in) {
    Polynomial current_value = {};
    Command cmd;
    int err;
    int ch;
    int comment = 0;

    while (!seek_char(&in, &ch) && ch > 0) {
        if (ch == '%') {
            while ((ch = fgetc(in)) != '\n');
            continue;
        }
        if (ch == '[') {
            while ((ch = fgetc(in)) != ']');
            continue;
        }

        if (!read_command(in, &cmd, ch)) {
            err = handle_command(in, &current_value, cmd);
            if (err) {
                destroy_polynomial(&current_value);
                return err;
            }

            err = skip_to_semicolon(in);
            if (err) {
                destroy_polynomial(&current_value);
                return err;
            }
        }

    }

    destroy_polynomial(&current_value);

    err = ch;

    if (err == EOF)
        return 0;

    return err;
}

int read_command(FILE *in, Command *cmd, int first) {
    int ch;

    char buf[10] = {};
    int i = 0;
    buf[i++] = (char) first;
    buf[i] = '\0';

    while((ch = fgetc(in)) && is_letter(ch)) {
        buf[i++] = (char) ch;
        buf[i] = '\0';
    }

    if (ch != '(')
        return 1;

    if (is_str_equal(buf, "Add")) {
        *cmd = SUM;
    } else if (is_str_equal(buf, "Sub")) {
        *cmd = SUBTRACTION;
    } else if (is_str_equal(buf, "Mult")) {
        *cmd = MULTIPLICATION;
    } else if (is_str_equal(buf, "Div")) {
        *cmd = DIVISION;
    } else if (is_str_equal(buf, "Mod")) {
        *cmd = MODULUS;
    } else if (is_str_equal(buf, "Eval")) {
        *cmd = EVALUATION;
    } else if (is_str_equal(buf, "Diff")) {
        *cmd = DIFFERENTIATION;
    } else if (is_str_equal(buf, "Cmps")) {
        *cmd = COMPOSITION;
    } else {
        return 1;
    }

    return 0;
}

int handle_command(FILE *in, Polynomial *current, Command cmd) {
    Array args[2] = {};
    int err;
    err = create_arr(5, &args[0]);
    if (err)
        return err;

    err = create_arr(5, &args[1]);
    if (err)
        return err;

    int i = 0;
    int point;

    err = read_arguments(in, args, &i);
    if (err)
        return err;

    Polynomial polynomials[2] = {{}, {}};

    if (i == 1)
        copy_polynomial(&polynomials[0], *current);
    else
        parse_polynomial(args[0], &polynomials[0]);

    if (cmd != EVALUATION) {
        parse_polynomial(args[i - 1], &polynomials[1]);
        destroy_polynomial(current);
    } else {
        arr_to_value(args[i - 1], &point);
    }


    switch (cmd) {
        case SUM:
            add_polynomials(polynomials[0], polynomials[1], current);
            break;
        case SUBTRACTION:
            subtract_polynomials(polynomials[0], polynomials[1], current);
            break;
        case MULTIPLICATION:
            multiply_polynomials(polynomials[0], polynomials[1], current);
            break;
        case DIVISION:
            divide_polynomials(polynomials[0], polynomials[1], current);
            break;
        case MODULUS:
            modulus_polynomials(polynomials[0], polynomials[1], current);
            break;
        case EVALUATION:
            printf("%d\n", evaluate_point(polynomials[0], point));
            break;
        case DIFFERENTIATION:
            derive_polynomial(polynomials[0], current);
            break;
        case COMPOSITION:
            compose_polynomials(polynomials[0], polynomials[1], current);
            break;
        default:
            destroy(&args[0]);
            destroy(&args[1]);
            return throw_err(INCORRECT_OPTION);
    }

    if (cmd != EVALUATION)
        print_polynomial(*current);

    destroy(&args[0]);
    destroy(&args[1]);

    return 0;
}

int read_arguments(FILE *in, Array *args, int *n) {
    int ch;

    while ((ch = fgetc(in)) && ch > ' ' && ch != ')') {
        if (*n > 2)
            return throw_err(INCORRECT_INPUT_DATA);

        if (ch != ',')
            append(&args[*n], (char) ch);
        else {
            (*n)++;
        }
    }
    (*n)++;

    return 0;
}

int skip_to_semicolon(FILE *in) {
    int ch;

    while ((ch = fgetc(in)) > 0 && ch != ';');

    if (ch == ';')
        return 0;

    return throw_err(INCORRECT_INPUT_DATA);
}

int parse_polynomial(Array str, Polynomial *res) {  // TODO: add in-between search
    if (str.length == 0)
        return 1;

    int minus = 0;
    int coefficient = 0;
    int is_power = 0;
    int power = 0;
    int is_x = 0;
    int is_truly_x = 1;
    int prev_power = 0;
    int first = 1;
    int max_power = -1000000000;

    for (int i = 0; i < str.length; ++i) {
        char cur = str.val[i];

        if (first && cur == '-') {
            minus = 1;
        } else if (cur == '+' || cur == '-') {
            if (is_x && !power && is_truly_x)
                power = 1;

            int pwr_diff = abs(prev_power - power);

            if (pwr_diff > 1 && !first) {
                for (int j = 1; j < pwr_diff; ++j) {
                    int err = append_polynomial(res, 0);
                    if (err)
                        return err;
                }
            }

            coefficient = abs(coefficient) > 0 ? coefficient : 1;

            if (minus)
                coefficient *= -1;

            int err = append_polynomial(res, coefficient);
            if (err)
                return err;

            if (power > max_power)
                max_power = power;

            prev_power = power;
            first = 0;
            power = 0;
            coefficient = 0;
            is_x = 0;
            minus = 0;
            is_power = 0;
            is_truly_x = 1;

            if (cur == '-')
                minus = 1;

        } else if (is_num(cur)) {
            if (!is_power) {
                coefficient *= 10;
                coefficient += cur - '0';
            } else {
                power *= 10;
                power += cur - '0';
            }
        } else if (cur == 'x') {
            is_x = 1;
        } else if (cur == '^') {
            is_truly_x = 0;
            is_power = 1;
        } else {
            return 1;
        }
    }

    if (is_x && !power && is_truly_x)
        power = 1;

    int pwr_diff = abs(prev_power - power);

    if (pwr_diff > 1 && !first) {
        for (int j = 1; j < pwr_diff; ++j) {
            int err = append_polynomial(res, 0);
            if (err)
                return err;
        }
    }

    if (power > 0)
        coefficient = abs(coefficient) > 0 ? coefficient : 1;

    if (minus)
        coefficient *= -1;

    int err = append_polynomial(res, coefficient);
    if (err)
        return err;

    if (power > 0) {
        for (int j = power; j > 0; --j) {
            err = append_polynomial(res, 0);
            if (err)
                return err;
        }
    }

    if (power > max_power)
        max_power = power;

    if (is_power)
        return 1;

    res->n = max_power;

    return 0;
}


