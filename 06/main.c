#include <stdio.h>

#define AOC_IMPLEMENTATION
#include "../aoc.h"

typedef struct {
    int x;
    int y;
} Direction;

enum EDirection {
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

int main() {
}
