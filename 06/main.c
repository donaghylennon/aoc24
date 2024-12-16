#include <stdint.h>
#include <stdio.h>

#define AOC_IMPLEMENTATION
#include "../aoc.h"

typedef struct {
    int x;
    int y;
} Direction;

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

typedef struct {
    int x;
    int y;
} Position;

char get_pos(AOC_StringViewDA map, int x, int y);

uint64_t hash_int(void *a) {
    return *(int *)a;
}

int equals_function(void *a, void *b) {
    int *_a = a;
    int *_b = b;
    return *_a == *_b;
}

uint64_t hash_position(void *d) {
    Position *position = d;
    return position->x * 29 + position->y * 7;
}

int position_equals(void *d1, void *d2) {
    Position *position1 = d1;
    Position *position2 = d2;
    return position1->x == position2->x && position1->y == position2->y;
}

int main() {
    char *input = read_input("test");
    AOC_StringViewDA lines = aoc_sv_split(aoc_sv(input), '\n');
    AOC_HashTable h;
    hashtable_init(&h, hash_position, position_equals);

    int width = lines.data[0].length;
    int height = lines.length;

    int num_positions_visited = 1;
    Position current_pos;
    enum Direction current_direction = UP;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (get_pos(lines, i, j) == '^') {
                current_pos = (Position){ i, j };
                break;
            }
        }
    }

}

char get_pos(AOC_StringViewDA map, int x, int y) {
    return map.data[y].data[x];
}
