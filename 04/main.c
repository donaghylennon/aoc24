#include <stddef.h>
#include <stdio.h>

#define AOC_IMPLEMENTATION
#include "../aoc.h"

int count_occurrences(AOC_StringViewDA lines);

int main() {
    AOC_StringViewDA test = aoc_sv_split(aoc_sv("test,testo"), ',');
    for (int i = 0; i < test.length; i++) {
        aoc_sv_print(test.data[i]);
    }
    AOC_DA_FREE(test);
    const char *input = read_input("test");
    AOC_StringViewDA lines = aoc_sv_split(aoc_sv(input), '\n');
    AOC_DA_FREE(lines);
}

int count_occurrences(AOC_StringViewDA lines) {
}
