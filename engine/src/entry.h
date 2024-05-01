#pragma once

#include "core/application.h"
#include "core/logger.h"
#include "core/asserts.h"
#include "game_types.h"

extern b8 create_game(game* out_game);

int main(void) {

    game game_inst;
    KASSERT_MSG_RETURN(create_game(&game_inst), "Could not create game", -1);
    if (!game_inst.render || !game_inst.update || !game_inst.initialise || !game_inst.on_resize) {
        KFATAL("The game's function pointers must be assigned!");
        return -2;
    }
    KASSERT_NOT_NULL(!game_inst.render || !game_inst.update || !game_inst.initialise || !game_inst.on_resize, "Function pointer is missing", -2);
    KASSERT_NOT_NULL(!application_create(&game_inst), "Application failed to create", 1);
    KASSERT_NOT_NULL(!application_run(), "Application did not shutdown gracefully", 2);

    return 0;
}