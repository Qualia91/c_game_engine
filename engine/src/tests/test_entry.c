#include "tests/test_lib.h"

#include "core/logger.h"

#include "tests/darray_test.h"

int main(void) {
    test_results test_results = {0, 0};
    KDEBUG("DARRAY test suite running...");
    darray_test(&test_results);
    KDEBUG("DARRAY test suite results: \n\tPass: %d\n\tFail: %d", test_results.pass, test_results.fail);
    return test_results.fail == 0;
}