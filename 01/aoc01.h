#ifndef AOC_01_H
#define AOC_01_H

int *parse_input(char *input);
int count_input_nums(char *input);
void split_nums(int *nums, int count, int **left_nums, int **right_nums);
int total_min_distance(int *left_nums, int *right_nums, int count);
int similarity_score(int *left_nums, int *right_nums, int count);

#endif
