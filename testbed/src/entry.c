#include "game.h"

#include <entry.h>
#include <core/kmemory.h>

b8 create_game(game* out_game) {
    
    out_game->app_config.name = "Test app";
    out_game->app_config.start_pos_x = 100;
    out_game->app_config.start_pos_y = 100;
    out_game->app_config.start_width = 1280;
    out_game->app_config.start_height = 720;

    out_game->initialise = game_initialise;
    out_game->update = game_update;
    out_game->render = game_render;
    out_game->on_resize = game_on_resize;

    out_game->initialise(out_game);


    out_game->state = kallocate(sizeof(game_state), MEMORY_TAG_GAME);

    return TRUE;
}