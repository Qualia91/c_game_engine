#include "event.h"

#include "core/kmemory.h"
#include "core/logger.h"
#include "containers/darray.h"

typedef struct registered_event {
    void* listener;
    PFN_on_event callback;
} registered_event;

typedef struct event_code_entry {
    registered_event* events;
} event_code_entry;

#define MAX_MESSAGE_CODES 16384

typedef struct event_system_state {
    event_code_entry registered[MAX_MESSAGE_CODES];
} event_system_state;

static b8 is_initialised = FALSE;
static event_system_state state;

b8 event_initialise() {

    if (is_initialised == TRUE) {
        return FALSE;
    }

    kzero_memory(&state, sizeof(state));

    is_initialised = TRUE;

    return TRUE;

}

void event_shutdown() {
    for (u16 i = 0; i < MAX_MESSAGE_CODES; ++i) {
        if (state.registered[i].events != 0) {
            darray_destroy(state.registered[i].events);
            state.registered[i].events = 0;
        }
    }
    is_initialised = FALSE;
}

b8 event_register(u16 code, void* listener, PFN_on_event on_event) {

    if (is_initialised == FALSE) {
        KWARNING("Event system not initialised");
        return FALSE;
    }

    // Check if events is empty
    if (state.registered[code].events == 0) {
        state.registered[code].events = darray_create(registered_event);
    }

    // Duplicate detection
    u64 registered_events_length = darray_length(state.registered[code].events);
    for (u16 i = 0; i < registered_events_length; ++i) {
        if (state.registered[code].events[i].listener == listener) {
            KWARNING("Listener already registered, wont add it again");
            return FALSE;
        }
    }
    
    registered_event registered_event;
    registered_event.callback = on_event;
    registered_event.listener = listener;

    darray_push(state.registered[code].events, registered_event);

    return TRUE;

}

b8 event_unregister(u16 code, void* listener, PFN_on_event on_event) {

    if (is_initialised == FALSE) {
        KWARNING("Event system not initialised");
        return FALSE;
    }

    // Check if events is empty
    if (state.registered[code].events == 0) {
        KWARNING("No events, cant unregister event");
        return FALSE;
    }

    u64 registered_events_length = darray_length(state.registered[code].events);
    for (u16 i = 0; i < registered_events_length; ++i) {
        if (state.registered[code].events[i].listener == listener) {
            registered_event popped_event;
            darray_pop_at(state.registered[code].events, i, &popped_event);
            return TRUE;
        }
    }

    return FALSE;

}

b8 event_fire(u16 code, void* sender, event_context context) {

    if (is_initialised == FALSE) {
        KWARNING("Event system not initialised");
        return FALSE;
    }

    // Check if events is empty
    if (state.registered[code].events == 0) {
        return FALSE;
    }

    u64 registered_events_length = darray_length(state.registered[code].events);
    for (u16 i = 0; i < registered_events_length; ++i) {
        if (state.registered[code].events[i].callback(code, sender, state.registered[code].events[i].listener, context)) {
            // If returns true, fallthrough events
            return TRUE;
        }
    }

    return FALSE;

}
