#ifndef GAME__H
#define GAME__H

#include "log.h"
#include "ui/speech_box.h"
#include "world/entity/entity.h"
#include "world/world.h"

#define MAX_ENTITIES 1024 * 1024

typedef struct {
  world_t *world;
  entity_t *player;
  log_t *log;
  speech_t speech;

  int term_w, term_h;
  int is_running;
} game_t;

game_t *game_new();
void game_init(game_t *g);
void game_update(game_t *g, uint64_t dt);
void game_draw(game_t *g);

#endif
