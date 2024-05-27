#include "application.h"

#include "asserts.h"
#include "logger.h"
#include "platform/platform.h"
#include "game_types.h"
#include "core/event.h"
#include "core/input.h"

#include "core/kmemory.h"

typedef struct application_state {
    game* game_inst;
    b8 is_running;
    b8 is_suspended;
    platform_state platform_state;
    i16 width;
    i16 height;
    f64 last_time;
} application_state;

static b8 initialised = FALSE;

static application_state app_state;

b8 on_application_event(u16 code, void* sender, void* listener_inst, event_context context) {
    switch (code) {
        case EVENT_CODE_APPLICATION_QUIT:
            KINFO("EVENT_CODE_APPLICATION_QUIT received, shutting down.\n")
            app_state.is_running = FALSE;
            return TRUE;
    }
    return FALSE;
}

b8 on_application_key(u16 code, void* sender, void* listener_inst, event_context context) {
    switch (code) {
        case EVENT_CODE_KEY_PRESSED:
            if (context.data.u16[0] == KEY_ESCAPE) {
                event_context context = {};
                event_fire(EVENT_CODE_APPLICATION_QUIT, 0, context);
                return TRUE;
            }
            break;
        case EVENT_CODE_KEY_RELEASED:
            break;
    }
    return FALSE;
}

b8 application_create(game* game_inst) {
    KASSERT_MSG_RETURN(!initialised, "Application create called more than once", FALSE);

    app_state.game_inst = game_inst;

    app_state.is_running = TRUE;
    app_state.is_suspended = FALSE;

    if (!event_initialise()) {
        KERROR("Event system failed initialization. Application cannot continue.");
        return FALSE;
    }
    
    input_initialise();

    if (!event_register(EVENT_CODE_KEY_PRESSED, 0, on_application_key)) {
        KERROR("Application key pressed listener not set up");
        return FALSE;
    }

    if (!event_register(EVENT_CODE_KEY_RELEASED, 0, on_application_key)) {
        KERROR("Application key released listener not set up");
        return FALSE;
    }

    if (!event_register(EVENT_CODE_APPLICATION_QUIT, 0, on_application_event)) {
        KERROR("Application event listener not set up");
        return FALSE;
    }

    if (!platform_startup(
            &app_state.platform_state,
            game_inst->app_config.name,
            game_inst->app_config.start_pos_x,
            game_inst->app_config.start_pos_y,
            game_inst->app_config.start_width,
            game_inst->app_config.start_height)) {
        return FALSE;
    }

    KASSERT_MSG_RETURN(app_state.game_inst->initialise(app_state.game_inst), "Game failed to initialise", FALSE);

    app_state.game_inst->on_resize(app_state.game_inst, app_state.width, app_state.height);

    initialised = TRUE;

    return TRUE;
}

b8 application_run() {
    KINFO(get_memory_usage_string());
    while (app_state.is_running) {

        if (!platform_pump_messages(&app_state.platform_state)) {
            app_state.is_running = FALSE;
        }

        if (!app_state.is_suspended) {

            if (!app_state.game_inst->update(app_state.game_inst, (f32)0)) {
                KFATAL("Game update failed, shutting down");
                app_state.is_running = FALSE;
                break;
            }

            if (!app_state.game_inst->render(app_state.game_inst, (f32)0)) {
                KFATAL("Game render failed, shutting down");
                app_state.is_running = FALSE;
                break;
            }

            input_update(0);
        }
    }

    app_state.is_running = FALSE;
    
    input_shutdown();
    event_shutdown();
    platform_shutdown(&app_state.platform_state);

    return TRUE;
}