#pragma once

#include "defines.h"

typedef struct test_results {
    int pass;
    int fail;
} test_results;

#define ASSERT_EQUAL(expected, value, message) do { \
    __typeof__(expected) temp_expected = expected;  \
    __typeof__(value) temp_value = value;           \
    if (temp_expected != temp_value) {              \
        KDEBUG(message);                            \
        test_results->fail++;                       \
    } else {                                        \
        test_results->pass++;                       \
    }                                               \
} while (0)