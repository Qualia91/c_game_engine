#pragma once

#include "defines.h"

typedef struct event_context {
    // 128 bytes
    union {
        i64 i64[2];
        u64 i64[2];
        f64 i64[2];
        
        i32 i64[4];
        u32 i64[4];
        f32 i64[4];
        
        i16 i16[8];
        u16 u16[8];

        char c[16];
    } data;
} event_context;

typedef b8 (*PFN_on_event)(u16 code, void* sender, void* listener_inst, event_context data);

b8 event_initialise();
void event_shutdown();

KAPI void event_register(u16 code, void* listener, PFN_on_event on_event);
KAPI void event_unregister(u16 code, void* listener, PFN_on_event on_event);
void event_fire(u16 code, void* sender, PFN_on_event on_event);

// System internal event codes. Application should use codes beyond 255.
typedef enum system_event_code {
    // Shuts the application down on the next frame.
    EVENT_CODE_APPLICATION_QUIT = 0x01,

    // Keyboard key pressed.
    /* Context usage:
     * u16 key_code = data.data.u16[0];
     */
    EVENT_CODE_KEY_PRESSED = 0x02,

    // Keyboard key released.
    /* Context usage:
     * u16 key_code = data.data.u16[0];
     */
    EVENT_CODE_KEY_RELEASED = 0x03,

    // Mouse button pressed.
    /* Context usage:
     * u16 button = data.data.u16[0];
     */
    EVENT_CODE_BUTTON_PRESSED = 0x04,

    // Mouse button released.
    /* Context usage:
     * u16 button = data.data.u16[0];
     */
    EVENT_CODE_BUTTON_RELEASED = 0x05,

    // Mouse moved.
    /* Context usage:
     * u16 x = data.data.u16[0];
     * u16 y = data.data.u16[1];
     */
    EVENT_CODE_MOUSE_MOVED = 0x06,

    // Mouse moved.
    /* Context usage:
     * u8 z_delta = data.data.u8[0];
     */
    EVENT_CODE_MOUSE_WHEEL = 0x07,

    // Resized/resolution changed from the OS.
    /* Context usage:
     * u16 width = data.data.u16[0];
     * u16 height = data.data.u16[1];
     */
    EVENT_CODE_RESIZED = 0x08,

    MAX_EVENT_CODE = 0xFF
} system_event_code;