#ifndef GAME__H
#define GAME__H

#include "d_game.h"

game_t *game_new();
void game_init(game_t *g);
void game_update(game_t *g, uint64_t dt);
void game_draw(game_t *g);

#endif
