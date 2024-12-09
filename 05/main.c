#include <stdio.h>

#define AOC_IMPLEMENTATION
#include "../aoc.h"

typedef struct {
    int a;
    int b;
} OrderingRule;

typedef AOC_DA(OrderingRule) OrderingRules;

int main() {
    char *input = read_input("test");
    if (!input) {
        fprintf(stderr, "Failed to open input file");
    }
    AOC_StringViewDA lines = aoc_sv_split(aoc_sv(input), '\n');
    OrderingRules rules;
    for (int i = 0; i < lines.length; i++) {
        AOC_StringView line = lines.data[i];
        if (line.length == 0)
            break;
        AOC_StringViewDA pages = aoc_sv_split(line, '|');
        int a = atoi(pages.data[0].data);
        int b = atoi(pages.data[1].data);
        AOC_DA_FREE(pages);

        OrderingRule rule = {a, b};
        AOC_DA_APPEND(rules, rule);
    }

    for (int i = 0; i < rules.length; i++) {
        printf("Rule %i: %i, %i\n", i, rules.data[i].a, rules.data[i].b);
    }
    AOC_DA_FREE(lines);
    free(input);
    return 0;
}
