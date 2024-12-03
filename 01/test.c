#include "aoc01.h"
#include "assert.h"

void test_count_input_nums() {
    const char *test_string = "111 111 11";
    assert(count_input_nums(test_string) == 3);
}
