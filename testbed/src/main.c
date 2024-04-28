#include <core/logger.h>
#include <core/asserts.h>

// test
#include <platform/platform.h>

int main(void) {
    KFATAL("A test: %f", 3.14f);
    KERROR("A test: %f", 3.14f);
    KWARNING("A test: %f", 3.14f);
    KINFO("A test: %f", 3.14f);
    KDEBUG("A test: %f", 3.14f);
    KTRACE("A test: %f", 3.14f);

    platform_state state;

    if (platform_startup(&state, "Test window", 100, 100, 1280, 720)) {
        while (TRUE) {
            platform_pump_messages(&state);
        }
    }
    platform_shutdown(&state);

    return 0;
}