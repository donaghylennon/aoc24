#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define AOC_IMPLEMENTATION
#include "../aoc.h"

char *parse_number(char *p, int *result, int *success);
char *expect(char *p, char *expected, int *success);
int sum_valid_muls(char *input);
int sum_valid_muls_disable(char *input);

int main() {
    char *input = read_input("input");
    int total1 = sum_valid_muls(input);
    int total2 = sum_valid_muls_disable(input);
    printf("sum of valid muls: %i\n", total1);
    printf("sum of valid muls w/ disable: %i\n", total2);
    return 0;
}

int sum_valid_muls(char *input) {
    int total = 0;
    char *p = input;
    int success = 0;
    while (p) {
        int operand1, operand2;
        p = strstr(p, "mul(");
        if (!p)
            continue;
        p = expect(p, "mul(", &success);
        if (!success)
            continue;
        p = parse_number(p, &operand1, &success);
        if (!success)
            continue;
        p = expect(p, ",", &success);
        if (!success)
            continue;
        p = parse_number(p, &operand2, &success);
        if (!success)
            continue;
        p = expect(p, ")", &success);
        if (!success)
            continue;
        total += operand1 * operand2;
    }
    return total;
}

char *parse_number(char *p, int *result, int *success) {
    char buf[20];
    char *q = p;
    size_t i = 0;
    while (isdigit(*q)) {
        buf[i++] = *q++;
    }
    buf[i] = '\0';
    if (i > 0) {
        *result = atoi(buf);
        *success = 1;
        return q;
    } else {
        *success = 0;
        return p;
    }
}

char *expect(char *p, char *expected, int *success) {
    size_t n = strlen(expected);
    if (strncmp(p, expected, n)) {
        *success = 0;
        return p;
    } else {
        *success = 1;
        return p+n;
    }
}

int sum_valid_muls_disable(char *input) {
    int total = 0;
    char *p = input;
    char *q = input;
    int success = 0;
    int enabled = 1;
    while (p) {
        int operand1, operand2;
        q = strstr(p, "do");
        p = strstr(p, "mul(");
        if (!p)
            continue;
        while (q && q < p) {
            q = expect(q, "do()", &success);
            if (success) {
                enabled = 1;
            } else {
                q = expect(q, "don't()", &success);
                if (success) {
                    enabled = 0;
                }
            }
            q = strstr(q, "do");
        }
        p = expect(p, "mul(", &success);
        if (!success)
            continue;
        if (!enabled)
            continue;
        p = parse_number(p, &operand1, &success);
        if (!success)
            continue;
        p = expect(p, ",", &success);
        if (!success)
            continue;
        p = parse_number(p, &operand2, &success);
        if (!success)
            continue;
        p = expect(p, ")", &success);
        if (!success)
            continue;
        total += operand1 * operand2;
    }
    return total;
}
