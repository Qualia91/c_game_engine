#include "game.h"

#include <core/logger.h>

b8 game_initialise(game* game_inst) {
    KDEBUG("game init was called");
    return TRUE;
}

b8 game_update(game* game_inst, f32 delta_time) {
    return TRUE;
}

b8 game_render(game* game_inst, f32 delta_time) {
    return TRUE;
}

void game_on_resize(game* game_inst, u32 width, u32 height) {
    KDEBUG("game on_resize was called");
}