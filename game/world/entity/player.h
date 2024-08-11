#ifndef PLAYER__H
#define PLAYER__H

#include "../../../termbox2/termbox2.h"
#include "../../d_world.h"

extern entity_t *g_player;

entity_t *player_init(world_t *w);
void player_handle_event(entity_t *p, const struct tb_event ev);
void player_draw(entity_t *p);

#endif
