#ifndef __G_PLAYER__
#define __G_PLAYER__

#include "../termbox2/termbox2.h"
#include "d_world.h"

extern entity_t *g_player;

entity_t *player_init(world_t *w);
void player_handle_event(entity_t *p, const struct tb_event ev);
void player_draw(entity_t *p);

#endif
