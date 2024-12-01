#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_input();
int *parse_input(char *input);
int count_input_nums(char *input);
void split_nums(int *nums, int count, int **left_nums, int **right_nums);
int total_min_distance(int *left_nums, int *right_nums, int count);
void sort(int *arr, int count);
int similarity_score(int *left_nums, int *right_nums, int count);

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

char *read_input() {
    FILE *file = fopen("input", "rb");
    fseek(file, 0, SEEK_END);
    long bytes = ftell(file);
    rewind(file);

    char *input = malloc(bytes+1);

    fread(input, 1, bytes, file);
    input[bytes] = '\0';
    fclose(file);

    return input;
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

void sort(int *arr, int count) {
    for (int i = 1; i < count; i++) {
        for (int j = i; j > 0; j--) {
            if (arr[j] < arr[j-1]) {
                int temp = arr[j-1];
                arr[j-1] = arr[j];
                arr[j] = temp;
            }
        }
    }
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
