#ifndef ENTITY_BRAIN__H
#define ENTITY_BRAIN__H

#include "../../d_game.h"

typedef struct {
  game_t *game;
  entity_t *entity;
  const char *msg;
  const char *response;
} ent_brain_think_request_t;

typedef void (*ent_brain_think_callback)(ent_brain_think_request_t *);

void ent_brain_think_and_answer(ent_brain_think_request_t *r,
                                ent_brain_think_callback cb);

#endif
