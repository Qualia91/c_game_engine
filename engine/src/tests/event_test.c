#include "tests/event_test.h"

#include "core/event.h"
#include "core/logger.h"

b8 on_event(u16 code, void* sender, void* listener_inst, event_context context) {
    KDEBUG("Message received: %d", context.data.i16[0]);
    if (context.data.i16[0] != 123) {
        return FALSE;
    }
    return TRUE;
}

void event_test(test_results *test_results) {
    
    b8 init_response = event_initialise();
    ASSERT_EQUAL(TRUE, init_response, "Event system did not initialise");

    b8 register_response = event_register(EVENT_CODE_KEY_PRESSED, "test_listener", on_event);
    ASSERT_EQUAL(TRUE, init_response, "Event was not registered");

    event_context event_context;
    event_context.data.i16[0] = 123;

    b8 fire_response = event_fire(EVENT_CODE_KEY_PRESSED, "test_sender", event_context);
    ASSERT_EQUAL(TRUE, fire_response, "Event fire did not return true");
    
    event_shutdown();

    b8 register_after_shutdown_response = event_register(EVENT_CODE_KEY_PRESSED, "test_listener", on_event);
    ASSERT_EQUAL(FALSE, register_after_shutdown_response, "Event was registered after shutdown");

}

