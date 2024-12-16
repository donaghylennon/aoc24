#ifndef LD_H
#define LD_H

#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t len;
    const char *data;
} ldStringView;

ldStringView ld_sv(const char *cstring);
ldStringView ld_sv_substring(AOC_StringView sv, int start, int end);
int ld_sv_find(ldStringView sv, const char c);
int ld_sv_find_starting_at(ldStringView sv, const char c, int start_pos);
ldStringViewDA ld_sv_split(AOC_StringView sv, const char delim);
void ld_sv_print(ldStringView sv);

#define ld_da_declare(TYPE) \
    struct { \
        size_t len; \
        size_t cap; \
        TYPE *items; \
    }

#define ld_da_append()

#ifdef LD_IMPLEMENTATION

ldStringView ld_sv(const char *cstring) {
    return { strlen(cstring), cstring };
}

ldStringView ld_sv_substring(AOC_StringView sv, int start, int end) {
    return { end - start, &sv.data[start] };
}

int ld_sv_find(ldStringView sv, const char c) {
    for (int i = 0; i < sv.len; i++) {
        if (sv.data[i] == c)
            return i;
    }
    return -1;
}

int ld_sv_find_starting_at(ldStringView sv, const char c, int start_pos) {
    for (int i = start_pos; i < sv.len; i++) {
        if (sv.data[i] == c)
            return i;
    }
    return -1;
}

ldStringViewDA ld_sv_split(AOC_StringView sv, const char delim) {
    ldStringViewDA results = {0};
    ldStringView remaining = sv;
    int delim_pos = 0;
    while (remaining.len > 0) {
        delim_pos = ld_sv_find(remaining, delim);
        if (delim_pos < 0) {
            break;
        }
        ldStringView substring = ld_sv_substring(remaining, 0, delim_pos);
        ldDA_APPEND(results, substring);
        if (delim_pos < remaining.len)
            remaining = ld_sv_substring(remaining, delim_pos+1, remaining.len);
    }
    if (remaining.len > 0) {
        ldDA_APPEND(results, remaining);
    }
    return results;
}

void ld_sv_print(ldStringView sv) {
    for (int i = 0; i < sv.len; i++) {
        putchar(sv.data[i]);
    }
    putchar('\n');
}


#endif

#endif
