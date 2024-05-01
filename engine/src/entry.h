#pragma once

#include "core/application.h"
#include "core/logger.h"
#include "core/asserts.h"
#include "core/kmemory.h"

#include "game_types.h"

extern b8 create_game(game* out_game);

int main(void) {

    initialise_memory();
    initialise_logging();

    game game_inst;
    KASSERT_MSG_RETURN(create_game(&game_inst), "Could not create game", -1);
    KASSERT_NOT_NULL(game_inst.render, "Render function pointer is missing", -2);
    KASSERT_NOT_NULL(game_inst.update, "Update function pointer is missing", -2);
    KASSERT_NOT_NULL(game_inst.initialise, "Initialise function pointer is missing", -2);
    KASSERT_NOT_NULL(game_inst.on_resize, "On resize function pointer is missing", -2);
    KASSERT_NOT_NULL(application_create(&game_inst), "Application failed to create", 1);
    KASSERT_NOT_NULL(application_run(), "Application did not shutdown gracefully", 2);

    shutdown_logging();
    shutdown_memory();

    return 0;
}