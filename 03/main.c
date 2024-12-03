#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define AOC_IMPLEMENTATION
#include "../aoc.h"

char *parse_number(char *p, int *result);
char *expect(char *p, char *expected, int *success);

int main() {
    char *input = read_input("test");
    printf(input);
    return 0;
}

int sum_valid_muls(char *input) {
    char *p = strstr(input, "mul(");
    int success = 0;
    p = expect(p, "mul(", &success);
}

char *parse_number(char *p, int *result) {
    char buf[20];
    char *q = p;
    size_t i = 0;
    while (isdigit(*q)) {
        buf[i++] = *q++;
    }
    buf[i] = '\0';
    if (i > 0) {
        *result = atoi(buf);
        return q;
    } else {
        result = NULL;
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
