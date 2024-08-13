#ifndef WORLD__H
#define WORLD__H

// ====================
//      WORLD
// ====================

#include "d_world.h"
#include <stdint.h>

world_t *world_new(int w, int h, int max_ent);
entity_t *world_spawn(world_t *w, entity_t e);
void world_spawn_level(world_t *w, entity_t e);

void world_update(world_t *w);
void world_draw(world_t *w);
void world_draw_level(world_t *w);
void world_draw_dynamic(world_t *w);

void world_destroy(world_t *w, entity_t *e);

entity_t *world_get_entity(world_t *w, int x, int y, unsigned int mask);
entity_collection_t world_get_entities(world_t *w, int x, int y, int radius);

void world_gen_grass(world_t *w);

#endif
