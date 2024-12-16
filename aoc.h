#ifndef AOC_H
#define AOC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

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

#define AOC_DA_CONTAINS(arr, item, result) \
    result = 0; \
    for (int i = 0; i < (arr).length; i++) { \
        if (item == (arr).data[i]) { \
            result = 1; \
            break; \
        } \
    }


typedef struct {
    size_t length;
    const char *data;
} AOC_StringView;

typedef AOC_DA(AOC_StringView) AOC_StringViewDA;

#define HASHTABLE_INITIAL_CAP 64
typedef struct {
    size_t size;
    size_t capacity;
    void **buckets;
    uint64_t (*hash)(void *);
    int (*is_equal)(void *, void *);
} AOC_HashTable;


char *read_input(const char *filename);
AOC_StringView aoc_read_file(const char *filename);
AOC_StringView aoc_sv(const char *cstring);
void sort(int *arr, int count);
AOC_StringView aoc_sv_substring(AOC_StringView sv, int start, int end);
int aoc_sv_find(AOC_StringView sv, const char c);
int aoc_sv_find_starting_at(AOC_StringView sv, const char c, int start_pos);
AOC_StringViewDA aoc_sv_split(AOC_StringView sv, const char delim);
void aoc_sv_print(AOC_StringView sv);

void hashtable_init(AOC_HashTable *h, uint64_t (*hash_function)(void *), int (*equals_function)(void *, void *));
void hashtable_destroy(AOC_HashTable *h);
int hashtable_contains(AOC_HashTable *h, void *item);
int hashtable_add(AOC_HashTable *h, void *item);
void hashtable_resize(AOC_HashTable *h, size_t new_capacity);

#define AOC_IMPLEMENTATION
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

void hashtable_init(AOC_HashTable *h, uint64_t (*hash_function)(void *), int (*equals_function)(void *, void *)) {
    h->capacity = HASHTABLE_INITIAL_CAP;
    h->size = 0;
    h->hash = hash_function;
    h->is_equal = equals_function;
    h->buckets = malloc(HASHTABLE_INITIAL_CAP * sizeof(void *));
}

void hashtable_destroy(AOC_HashTable *h) {
    h->capacity = 0;
    h->size = 0;
    if (h->buckets)
        free(h->buckets);
    h->buckets = NULL;
    h->hash = NULL;
}

int hashtable_contains(AOC_HashTable *h, void *item) {
    uint64_t hash = h->hash(item);
    size_t index = hash%h->capacity;
    while (h->buckets[index]) {
        if (h->is_equal(h->buckets[index], item)) {
            return 1;
        }
        index = (index + 1) % h->capacity;
    }
    return 0;
}

int hashtable_add(AOC_HashTable *h, void *item) {
    if (h->size >= h->capacity - 1) {
        hashtable_resize(h, h->capacity*2);
    }
    uint64_t hash = h->hash(item);
    size_t index = hash%h->capacity;
    while (h->buckets[index]) {
        if (h->is_equal(h->buckets[index], item)) {
            return 1;
        }
        index = (index + 1) % h->capacity;
    }
    h->buckets[index] = item;
    h->size++;
    return 0;
}

void hashtable_resize(AOC_HashTable *h, size_t new_capacity) {
    if (h->capacity < new_capacity) {
        size_t old_capacity = h->capacity;
        void **new_buckets = malloc(new_capacity * sizeof(void *));
        for (size_t i = 0; i < old_capacity; i++) {
            if (h->buckets[i]) {
                uint64_t hash = h->hash(h->buckets[i]);
                size_t index = hash % new_capacity;
                while (new_buckets[index]) {
                    index = (index + 1) % new_capacity;
                }
                new_buckets[index] = h->buckets[i];
            }
        }
        h->capacity = new_capacity;
        free(h->buckets);
        h->buckets = new_buckets;
    }
}

#endif

#endif
