#include "event.h"

#include "core/kmemory.h"

typedef struct registered_event {
    void* listener;
    PFN_on_event callback;
} registered_event;

typedef struct event_code_entry {
    registered_event* events;
} event_code_entry;

#define MAX_MESSAGE_CODES 16384

typedef struct event_syste_state {
    event_code_entry registered[MAX_MESSAGE_CODES];
} event_system_state;

static b8 is_initialised = FALSE;
static event_syste_state state;

b8 event_initialise() {

}

void event_shutdown() {

}

KAPI void event_register(u16 code, void* listener, PFN_on_event on_event) {

}

KAPI void event_unregister(u16 code, void* listener, PFN_on_event on_event) {

}

void event_fire(u16 code, void* sender, PFN_on_event on_event) {

}
