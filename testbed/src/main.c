#include <core/logger.h>
#include <core/asserts.h>

int main(void) {
    KFATAL("A test: %f", 3.14f);
    KERROR("A test: %f", 3.14f);
    KWARNING("A test: %f", 3.14f);
    KINFO("A test: %f", 3.14f);
    KDEBUG("A test: %f", 3.14f);
    KTRACE("A test: %f", 3.14f);

    KASSERT(1 == 0);

    return 0;
}