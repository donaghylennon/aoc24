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
    }

#define AOC_DA_INITIAL_CAP 64
#define AOC_DA_APPEND(arr, value) do { \
        if ((arr).length >= (arr).capacity) { \
            (arr).capacity = (arr).capacity==0 ? AOC_DA_INITIAL_CAP : (arr).capacity*2; \
            (arr).data = realloc((arr).data, (arr).capacity * sizeof((arr).data[0])); \
        } \
        (arr).data[(arr).length++] = (value); \
    } while (0)
#define AOC_DA_FREE(arr) free((arr).data)

typedef struct {
    size_t length;
    const char *data;
} AOC_String;

typedef struct {
    size_t length;
    const char *data;
} AOC_StringView;

typedef struct {
    size_t length;
    const char *data;
} AOC_Array;

typedef AOC_DA(AOC_StringView) AOC_StringViewDA;

char *read_input(const char *filename);
AOC_StringView aoc_read_file(const char *filename);
AOC_StringView aoc_sv(const char *cstring);
void sort(int *arr, int count);
AOC_StringView aoc_sv_substring(AOC_StringView sv, int start, int end);
int aoc_sv_find(AOC_StringView sv, const char c);
AOC_StringViewDA aoc_sv_split(AOC_StringView sv, const char delim);
void aoc_sv_print(AOC_StringView sv);

#ifdef AOC_IMPLEMENTATION

AOC_StringView aoc_sv(const char *cstring) {
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

AOC_StringView aoc_sv_substring(AOC_StringView sv, int start, int end) {
    AOC_StringView new_sv = { end - start, &sv.data[start] };
    return new_sv;
}

int aoc_sv_find(AOC_StringView sv, const char c) {
    for (int i = 0; i < sv.length; i++) {
        if (sv.data[i] == c)
            return i;
    }
    return -1;
}

AOC_StringViewDA aoc_sv_split(AOC_StringView sv, const char delim) {
    AOC_StringViewDA results = {0};
    int substring_start = 0;
    int count = 0;
    AOC_StringView remaining = sv;
    while (substring_start < sv.length) {
        int j = aoc_sv_find(remaining, delim);
        if (j < 0) {
            break;
        }
        if (j == substring_start) {
            substring_start++;
            continue;
        }
        AOC_StringView substring = aoc_sv_substring(remaining, substring_start, j);
        AOC_DA_APPEND(results, substring);
        substring_start = j+1;
        remaining = aoc_sv_substring(remaining, substring_start, remaining.length);
    }
    if (substring_start < sv.length) {
        AOC_DA_APPEND(results, remaining);
    }
    return results;
}

void aoc_sv_print(AOC_StringView sv) {
    for (int i = 0; i < sv.length; i++) {
        putchar(sv.data[i]);
    }
    putchar('\n');
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
