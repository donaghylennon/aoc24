
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "../aoc.h"

int count_input_nums(char *input) {
    int count = 0;
    char *p = input;
    while (*p != '\0') {
        while (*p != '\0' && !isspace(*p++))
            ;
        count++;
        while(isspace(*p))
            p++;
    }
    return count;
}

int *parse_input(char *input) {
    int total_nums = count_input_nums(input);
    int *nums = malloc(total_nums * sizeof(int));
    char *number = strtok(input, " \n");
    for (int i = 0; number != NULL && i < total_nums; i++) {
        nums[i] = atoi(number);
        number = strtok(NULL, " \n");
    }
    return nums;
}

void split_nums(int *nums, int count, int **left_nums, int **right_nums) {
    int lcount = count/2;
    int rcount = count - lcount;
    *left_nums = malloc(lcount * sizeof(int));
    *right_nums = malloc(rcount * sizeof(int));
    for (int i = 0; i < count; i++) {
        if (!(i % 2)) {
            (*left_nums)[i/2] = nums[i];
        } else {
            (*right_nums)[i/2] = nums[i];
        }
    }
}

int total_min_distance(int *left_nums, int *right_nums, int count) {
    sort(left_nums, count);
    sort(right_nums, count);
    int total_min_distance = 0;
    for (int i = 0; i < count; i++) {
        total_min_distance += abs(left_nums[i] - right_nums[i]);
    }
    return total_min_distance;
}

int similarity_score(int *left_nums, int *right_nums, int count) {
    int score = 0;
    for (int i = 0; i < count; i++) {
        int occurrences = 0;
        for (int j = 0; j < count; j++) {
            if (left_nums[i] == right_nums[j])
                occurrences++;
        }
        score += left_nums[i] * occurrences;
    }
    return score;
}
