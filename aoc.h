#ifndef AOC_H
#define AOC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AOC_DA(T) \
    struct { \
        size_t length; \
        size_t capacity; \
        T *data; \
    };

#define AOC_DA_INITIAL_CAP 64
#define AOC_DA_APPEND(T, arr, value) do { \
        if ((arr).length >= (arr).capacity) { \
            (arr).capacity = (arr).capacity==0 ? AOC_DA_INITIAL_CAP : (arr).capacity*2; \
            (arr).data = realloc((arr).data, (arr).capacity * sizeof((arr).data[0])); \
        } \
        (arr).data[(arr).length++] = (value); \
    } while (0)

typedef struct {
    size_t length;
    const char *data;
} AOC_String;

typedef struct {
    size_t length;
    const char *data;
} AOC_StringView;

char *read_input(const char *filename);
AOC_StringView aoc_read_file(const char *filename);
AOC_StringView aoc_str(const char *cstring);
void sort(int *arr, int count);
#define AOC_IMPLEMENTATION
#ifdef AOC_IMPLEMENTATION

AOC_StringView aoc_str(const char *cstring) {
    return (AOC_StringView){ strlen(cstring), cstring };
}

AOC_StringView aoc_read_file(const char *filename) {
    FILE *file = fopen("input", "rb");
    fseek(file, 0, SEEK_END);
    long result = ftell(file);
    if (result > 0) {
        return (AOC_StringView){ 0, NULL };
    }
    size_t length = (size_t)result;
    rewind(file);

    char *data = malloc(length+1);

    fread(data, 1, length, file);
    data[length] = '\0';
    fclose(file);

    return (AOC_StringView){ length, data };
}

int aoc_sv_split(AOC_StringView sv, const char delim) {
    return 0;
}

char *read_input(const char *filename) {
    FILE *file = fopen(filename, "rb");
    fseek(file, 0, SEEK_END);
    long bytes = ftell(file);
    rewind(file);

    char *input = malloc(bytes+1);

    fread(input, 1, bytes, file);
    input[bytes] = '\0';
    fclose(file);

    return input;
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
#endif

#endif
