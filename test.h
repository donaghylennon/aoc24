#include <stdio.h>

#define ASSERT(cond, message) do { \
    if (!cond) { \
        printf("\033[31mFailed assertion\033[0m: %s\n", message); \
        return; \
    } \
} while (0)

#define ASSERT_EQUALS(expected, actual, message) do { \
    if (expected != actual) { \
        printf("\033[31mFailed assertion\033[0m: %s\n", message); \
        printf("\t\033[31mExpected\033[0m %s\n", #expected); \
        printf("\t\033[31mGot     \033[0m %s\n", #actual); \
        return; \
    } \
} while (0)
