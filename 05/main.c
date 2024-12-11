#include <stdio.h>
#include <stdbool.h>

#define AOC_IMPLEMENTATION
#include "../aoc.h"

typedef struct {
    int a;
    int b;
} OrderingRule;

typedef AOC_DA(OrderingRule) OrderingRules;
typedef AOC_DA(int) IntDynArray;

int update_is_valid(IntDynArray update, OrderingRules rules);
void sort_update(IntDynArray update, OrderingRules rules);

int main() {
    char *input = read_input("input");
    if (!input) {
        fprintf(stderr, "Failed to open input file");
    }
    AOC_StringViewDA lines = aoc_sv_split(aoc_sv(input), '\n');
    OrderingRules rules = {0};
    int updates_start;
    for (int i = 0; i < lines.length; i++) {
        AOC_StringView line = lines.data[i];
        if (line.length == 0) {
            updates_start = i+1;
            break;
        }
        AOC_StringViewDA pages = aoc_sv_split(line, '|');
        int a = atoi(pages.data[0].data);
        int b = atoi(pages.data[1].data);
        AOC_DA_FREE(pages);

        OrderingRule rule = {a, b};
        AOC_DA_APPEND(rules, rule);
    }

    int total_middle_of_valid_updates = 0;
    int total_middle_of_corrected_updates = 0;

    for (int i = updates_start; i < lines.length; i++) {
        AOC_StringView line = lines.data[i];
        AOC_StringViewDA pages_string = aoc_sv_split(line, ',');
        IntDynArray pages = {0};
        for (int page_index = 0; page_index < pages_string.length; page_index++)
            AOC_DA_APPEND(pages, atoi(pages_string.data[page_index].data));

        if (update_is_valid(pages, rules)) {
            total_middle_of_valid_updates += pages.data[pages.length/2];
        } else {
            sort_update(pages, rules);
            total_middle_of_corrected_updates += pages.data[pages.length/2];
        }

        AOC_DA_FREE(pages_string);
        AOC_DA_FREE(pages);
    }

    AOC_DA_FREE(lines);
    free(input);

    printf("Total middle of valid updates: %i\n", total_middle_of_valid_updates);
    printf("Total middle of corrected updates: %i\n", total_middle_of_corrected_updates);
    return 0;
}

int update_is_valid(IntDynArray update, OrderingRules rules) {
    bool passed_rules = true;
    IntDynArray processed_pages = {0};
    for (int j = 0; j < update.length; j++) {
        int page = update.data[j];

        for (int k = 0; k < rules.length && passed_rules; k++) {
            OrderingRule rule = rules.data[k];
            if (page == rule.a) {
                bool failed_rule = false;
                AOC_DA_CONTAINS(processed_pages, rule.b, failed_rule);
                if (failed_rule) {
                    passed_rules = false;
                }
            }
        }

        if (passed_rules) {
            AOC_DA_APPEND(processed_pages, page);
        } else {
            break;
        }
    }
    AOC_DA_FREE(processed_pages);
    return passed_rules;
}

void sort_update(IntDynArray update, OrderingRules rules) {
    int i = 0;
    while (i < update.length) {
        int page = update.data[i];
        for (int j = i-1; j >= 0; j--) {
            int prev_page = update.data[j];

            for (int k = 0; k < rules.length; k++) {
                OrderingRule rule = rules.data[k];
                if (page == rule.a && prev_page == rule.b) {
                    
                    for (int p = j; p < i; p++) {
                        update.data[p] = update.data[p+1];
                    }
                    update.data[i] = prev_page;
                    i--;
                    break;
                }
            }
        }
        i++;
    }
}
