#include <stdlib.h>
#include <stdio.h>

#include "aoc01.h"
#define AOC_IMPLEMENTATION
#include "../aoc.h"

int main() {
    char *input = read_input();
    int count = count_input_nums(input);
    int *nums = parse_input(input);
    free(input);
    int *left_nums, *right_nums;
    split_nums(nums, count, &left_nums, &right_nums);
    free(nums);
    int total = total_min_distance(left_nums, right_nums, count/2);
    int sim_score = similarity_score(left_nums, right_nums, count/2);
    free(left_nums);
    free(right_nums);
    printf("total: %i\n", total);
    printf("similarity score: %i\n", sim_score);
    return 0;
}
