#include "world.h"

#include "../entity.h"
#include "../termbox2/termbox2.h"

#include <stdlib.h>

int get_pos1d(world_t *w, int x, int y) { return w->size.x * y + x; }

world_t *world_new(int w, int h, int max_ent) {
  world_t *world = (world_t *)malloc(sizeof(world_t));

  v2i size = {w, h};
  world->size = size;

  world->level = (entity_t *)malloc(w * h * sizeof(entity_t));

  world->max_entities = max_ent;
  world->entities = (entity_t *)malloc(max_ent * sizeof(entity_t));
  for (int i = 0; i < max_ent; i++) {
    world->entities[i] = ENT_INVALID;
  }
  return world;
}

void world_spawn(world_t *w, entity_t e) {
  if (!ent_isdynamic(&e)) {
    world_spawn_level(w, e);
  } else {
    for (int i = 0; i < w->max_entities; i++) {
      if (!ent_isvalid(&w->entities[i])) {
        w->entities[i] = e;
        return;
      }
    }
  }
}

void world_spawn_level(world_t *w, entity_t e) {
  entity_t *le = world_get_entity(w, e.x, e.y, 0);
  if (ent_isvalid(le)) {
    return;
  }

  int p = get_pos1d(w, e.x, e.y);
  w->level[p] = e;
}

void world_destroy(world_t *w, entity_t *e) { ent_destroy(e); }

void world_update(world_t *w) {
  for (int i = 0; i < w->max_entities; i++) {
    if (!ent_isvalid(&w->entities[i])) {
      continue;
    }
    ent_update(&w->entities[i]);
  }
}

void world_draw(world_t *w) {
  world_draw_level(w);
  world_draw_dynamic(w);
}

void world_draw_level(world_t *w) {
  int sz = w->size.x * w->size.y;
  for (int i = 0; i < sz; i++) {
    entity_t e = w->level[i];
    if (!ent_isvalid(&e)) {
      continue;
    }

    tb_print(e.x, e.y, TB_DIM, 0, e.symbol);
    // ent_draw(&w->entities[i]);
  }
}

void world_draw_dynamic(world_t *w) {
  for (int i = 0; i < w->max_entities; i++) {
    entity_t e = w->entities[i];
    if (!ent_isvalid(&e)) {
      continue;
    }

    tb_print(e.x, e.y, 0, 0, e.symbol);
    // ent_draw(&w->entities[i]);
  }
}

entity_t *world_get_entity(world_t *w, int x, int y, unsigned int mask) {

  if ((mask & ENT_MASK_DYNAMIC) > 0) {
    for (int i = 0; i < w->max_entities; i++) {
      entity_t *e = &w->entities[i];
      if (!ent_isvalid(e)) {
        continue;
      }

      if (e->x == x && e->y == y) {
        return e;
      }
    }

  } else {
    int p = get_pos1d(w, x, y);
    entity_t *e = &w->level[p];
    return e;
  }

  return &ENT_INVALID;
}
