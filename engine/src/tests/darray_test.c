#include "tests/darray_test.h"

#include "containers/darray.h"
#include "core/logger.h"

void darray_test(test_results *test_results) {

    int* array = darray_create(int);
    int a;

    darray_push(array, 1);
    darray_push(array, 2);
    ASSERT_EQUAL(2, darray_length(array), "Array size was not 2");

    darray_pop(array, &a);
    ASSERT_EQUAL(2, a, "Last entry in array was not 2");
    ASSERT_EQUAL(1, darray_length(array), "Array size was not 1");

    darray_pop(array, &a);
    ASSERT_EQUAL(1, a, "Last entry in array was not 1");
    ASSERT_EQUAL(0, darray_length(array), "Array size was not 0");

    darray_push(array, 1);
    darray_push(array, 2);
    darray_insert_at(array, 1, 3);
    ASSERT_EQUAL(3, array[1], "Index 1 in array  was not 3");
    ASSERT_EQUAL(3, darray_length(array), "Array size was not 3");

    darray_pop_at(array, 1, &a);
    ASSERT_EQUAL(3, a, "Last entry in array was not 3");
    ASSERT_EQUAL(2, darray_length(array), "Array size was not 2");

    darray_pop(array, &a);
    ASSERT_EQUAL(2, a, "Last entry in array was not 2");
    ASSERT_EQUAL(1, darray_length(array), "Array size was not 1");

    darray_pop(array, &a);
    ASSERT_EQUAL(1, a, "Last entry in array was not 1");
    ASSERT_EQUAL(0, darray_length(array), "Array size was not 0");

}