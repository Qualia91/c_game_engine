#include "tests/darray_test.h"

#include "containers/darray.h"
#include "core/logger.h"

void darray_test(test_results *test_results) {

    int* array = darray_create(int);
    darray_push(array, 1);
    darray_push(array, 2);
    int a;
    darray_pop(array, &a);

    ASSERT_EQUAL(2, a, "Last entry in array was not 2");

    int b;
    darray_pop(array, &b);

}