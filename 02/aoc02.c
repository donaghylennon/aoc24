#include <stdio.h>
#include <ctype.h>

#define AOC_IMPLEMENTATION
#include "../aoc.h"

size_t parse_line(char *input, int *buf, int buflen);
int is_report_safe(int *nums, size_t len);
int is_report_safe_dampened(int *nums, size_t len);
int total_safe_reports(char *input);
int total_safe_reports_dampened(char *input);

int main() {
    char *input = read_input();
    int total_safe = total_safe_reports(input);
    int total_safe_dampened = total_safe_reports_dampened(input);
    printf("total safe reports: %i\n", total_safe);
    printf("total safe reports dampened: %i\n", total_safe_dampened);
    return 0;
}

size_t parse_line(char *input, int *buf, int buflen) {
    char *p = input;
    size_t i = 0;
    while (p && *p && *p != '\n') {
        while (isspace(*p))
            p++;
        char num[5];
        size_t j = 0;
        while (isdigit(*p))
            num[j++] = *p++;
        num[j] = '\0';
        if (j > 0)
            buf[i++] = atoi(num);
    }
    return i;
}

int total_safe_reports(char *input) {
    int total = 0;
    int nums[10];
    char *p = input;
    size_t count = parse_line(p, nums, 10);
    while (count > 0) {
        if (is_report_safe(nums, count))
            total++;
        p = strchr(p, '\n');
        if (p)
            p++;
        count = parse_line(p, nums, 10);
    }
    return total;
}

int is_report_safe(int *nums, size_t len) {
    int prev = nums[0];
    int prev_diff = 0;
    for (int i = 1; i < len; i++) {
        int diff = nums[i] - prev;
        if (diff == 0 || abs(diff) > 3 || diff*prev_diff < 0)
            return 0;
        prev = nums[i];
        prev_diff = diff;
    }
    return 1;
}

int is_report_safe_dampened(int *nums, size_t len) {
    int prev_diff = 0;
    int skips = 0;
    int i = 0;
    if (is_report_safe(nums, len)) {
        return 1;
    } else {
        int nums_adjusted[10];
        for (int i = 0; i < len; i++) {
            int k = 0;
            for (int j = 0; j < len; j++) {
                if (i!=j)
                    nums_adjusted[k++] = nums[j];
            }
            if (is_report_safe(nums_adjusted, len-1))
                return 1;
        }
        return 0;
    }
}

int total_safe_reports_dampened(char *input) {
    int total = 0;
    int nums[10];
    char *p = input;
    size_t count = parse_line(p, nums, 10);
    while (count > 0) {
        if (is_report_safe_dampened(nums, count))
            total++;
        p = strchr(p, '\n');
        if (p)
            p++;
        count = parse_line(p, nums, 10);
    }
    return total;
}
