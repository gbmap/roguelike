#ifndef GAME__H
#define GAME__H

#include "d_game.h"

game_t *G_New();
void G_Init(game_t *g);
void G_Update(game_t *g, uint64_t dt);
void G_Draw(game_t *g);

#endif
