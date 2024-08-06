
#ifndef WORLD__H
#define WORLD__H

#define WRLD_DYNAMIC 0b0010
#define WRLD_STATIC 0b0001

// ====================
//      WORLD
// ====================

#include "../entity.h"

typedef struct {
  int x;
  int y;
} v2i;

typedef struct {
  v2i size;

  entity_t *level;

  int max_entities;
  entity_t *entities;
} world_t;

world_t *world_new(int w, int h, int max_ent);
void world_spawn(world_t *w, entity_t e);
void world_spawn_level(world_t *w, entity_t e);

void world_update(world_t *w);
void world_draw(world_t *w);
void world_draw_level(world_t *w);
void world_draw_dynamic(world_t *w);

void world_destroy(world_t *w, entity_t *e);

entity_t *world_get_entity(world_t *w, int x, int y, unsigned int mask);

#endif
