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

typedef struct {

} HT_Bucket;

#define AOC_HT_BUCKET(T) \
    struct T##_Bucket { \
        T item; \
        T##_Bucket *prev; \
        T##_Bucket *next; \
    }

#define AOC_HM_ENTRY(K, V) \
    struct K##_##V##_Entry { \
        K key; \
        V value; \
    }

#define AOC_HASHTABLE(T) \
    struct { \
        T **buckets; \
        size_t size; \
        size_t capacity; \
    }

typedef struct int_bucket {
    int item;
    struct int_bucket *prev;
    struct int_bucket *next;
} IntBucket;

#define AOC_HASHTABLE_INITIAL_SIZE 64
typedef struct {
    IntBucket **buckets;
    size_t size;
    size_t capacity;
} IntHashSet;

char *read_input(const char *filename);
AOC_StringView aoc_read_file(const char *filename);
AOC_StringView aoc_sv(const char *cstring);
void sort(int *arr, int count);
AOC_StringView aoc_sv_substring(AOC_StringView sv, int start, int end);
int aoc_sv_find(AOC_StringView sv, const char c);
int aoc_sv_find_starting_at(AOC_StringView sv, const char c, int start_pos);
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

int aoc_sv_find_starting_at(AOC_StringView sv, const char c, int start_pos) {
    for (int i = start_pos; i < sv.length; i++) {
        if (sv.data[i] == c)
            return i;
    }
    return -1;
}

AOC_StringViewDA aoc_sv_split(AOC_StringView sv, const char delim) {
    AOC_StringViewDA results = {0};
    AOC_StringView remaining = sv;
    int delim_pos = 0;
    while (remaining.length > 0) {
        delim_pos = aoc_sv_find(remaining, delim);
        if (delim_pos < 0) {
            break;
        }
        AOC_StringView substring = aoc_sv_substring(remaining, 0, delim_pos);
        AOC_DA_APPEND(results, substring);
        if (delim_pos < remaining.length)
            remaining = aoc_sv_substring(remaining, delim_pos+1, remaining.length);
    }
    if (remaining.length > 0) {
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
    if (!file)
        return NULL;
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

/*** Hash Table ***/

IntHashSet create_int_hashset() {
    IntHashSet h;
    h.buckets = malloc(AOC_HASHTABLE_INITIAL_SIZE * sizeof(struct int_bucket));
    memset(h.buckets, 0, AOC_HASHTABLE_INITIAL_SIZE * sizeof(struct int_bucket *));
    h.capacity = AOC_HASHTABLE_INITIAL_SIZE;
    h.size = 0;
}

/******************/
#endif

#endif
