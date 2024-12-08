#include <stddef.h>
#include <stdio.h>

#define AOC_IMPLEMENTATION
#include "../aoc.h"

int count_occurrences(AOC_StringViewDA lines);
int count_occurrences_starting_at(AOC_StringViewDA lines, int x, int y);
int count_x_mas(AOC_StringViewDA lines);
int is_x_mas(AOC_StringViewDA lines, int x, int y);

int main() {
    AOC_StringViewDA test = aoc_sv_split(aoc_sv("test,testo"), ',');
    for (int i = 0; i < test.length; i++) {
        aoc_sv_print(test.data[i]);
    }
    AOC_DA_FREE(test);
    const char *input = read_input("input");
    AOC_StringViewDA lines = aoc_sv_split(aoc_sv(input), '\n');
    int c = count_occurrences(lines);
    int cx = count_x_mas(lines);
    printf("XMAS Occurrences: %i\n", c);
    printf("X-MAS Occurrences: %i\n", cx);
    AOC_DA_FREE(lines);
}

int count_occurrences(AOC_StringViewDA lines) {
    int total_occurrences = 0;
    int width = lines.data[0].length;
    int height = lines.length;
    for (int y = 0; y < lines.length; y++) {
        int remaining_start = 0;
        int remaining_width = width;
        AOC_StringView line_remaining = lines.data[y];
        int x = aoc_sv_find(lines.data[y], 'X');
        while (x >= 0 && x < remaining_width) {
            total_occurrences += count_occurrences_starting_at(lines, remaining_start+x, y);
            if (x < remaining_width) {
                remaining_start += x+1;
                line_remaining = aoc_sv_substring(line_remaining, x+1, remaining_width);
                x = aoc_sv_find(line_remaining, 'X');
                remaining_width = line_remaining.length;
            }
        }
    }
    return total_occurrences;
}

int count_occurrences_starting_at(AOC_StringViewDA lines, int x, int y) {
    int count = 0;
    int width = lines.data[0].length;
    int height = lines.length;
    char xmas[] = "XMAS";
    for (int x_direction = -1; x_direction <= 1; x_direction++) {
        for (int y_direction = -1; y_direction <= 1; y_direction++) {
            int matching_chars = 0;
            for (int i = 0; i < 4; i++) {
                int x_pos = x + x_direction*i;
                int y_pos = y + y_direction*i;
                if (x_pos < 0 || x_pos >= width || y_pos < 0 || y_pos >= height
                        || lines.data[y_pos].data[x_pos] != xmas[i]) {
                    break;
                }
                matching_chars++;
            }
            if (matching_chars == 4)
                count++;
        }
    }
    return count;
}

int count_x_mas(AOC_StringViewDA lines) {
    int total_occurrences = 0;
    int width = lines.data[0].length;
    int height = lines.length;
    for (int y = 0; y < height; y++) {
        AOC_StringView line = lines.data[y];
        int x = aoc_sv_find(line, 'A');
        while (x >= 0 && x < width) {
            if (is_x_mas(lines, x, y))
                total_occurrences++;
            x = aoc_sv_find_starting_at(line, 'A', x+1);
        }
    }
    return total_occurrences;
}

int is_x_mas(AOC_StringViewDA lines, int x, int y) {
    if (lines.data[y].data[x] != 'A' || x == 0 || x+1 >= lines.data[0].length
            || y == 0 || y+1 >= lines.length)
        return 0;
    int num_mas = 0;
    if ((lines.data[y+1].data[x+1] == 'S' && lines.data[y-1].data[x-1] == 'M')
    || (lines.data[y+1].data[x+1] == 'M' && lines.data[y-1].data[x-1] == 'S')) {
            num_mas++;
    }
    if ((lines.data[y-1].data[x+1] == 'S' && lines.data[y+1].data[x-1] == 'M')
    || (lines.data[y-1].data[x+1] == 'M' && lines.data[y+1].data[x-1] == 'S')) {
            num_mas++;
    }
    if (num_mas == 2)
        return 1;
    return 0;
}
