#include "g_entity.h"
#include "../termbox2/termbox2.h"
#include "ui/speech_box.h"
#include "world/world.h"

#include "world/entity/entity_brain.h"
#include <string.h>

entity_t ENT_INVALID = {-1, -1, -1, 0, "\0"};

void E_Update(entity_t *e) {
  if (e->mask & ENT_MASK_PLAYER) {
    return;
  }

  if (e->mask & ENT_MASK_DYNAMIC) {
    int d = rand() % 2 == 0 ? -1 : 1;
    if (rand() % 2 == 0) {
      e->x += d;
    } else {
      e->y += d;
    }
  }
}

void E_Draw(entity_t *e) { tb_print(e->x, e->y, 0, 0, e->symbol); }
int E_IsValid(entity_t* e) { return (e->mask & ENT_MASK_VALID) > 1; }
int E_IsDynamic(entity_t *e) { return e->mask & ENT_MASK_DYNAMIC; }
void E_Kill(entity_t *e) { e->mask = 0; }

// ============
//
//

void ent_say(entity_t *e, game_t *g, const char *msg) {
  speech_push(&g->speech, msg, e);

  entity_collection_t ents_heard = world_get_entities(g->world, e->x, e->y, 10);
  for (int i = 0; i < ents_heard.count; i++) {
    entity_t *eh = ents_heard.entities[i];
    if (eh == e) {
      continue;
    }

    ent_hear(eh, g, msg);
  }
}

void cb_ent_think(ent_brain_think_request_t *r) {
  speech_push(&r->game->speech, r->response, r->entity);
  free(r);
}

void ent_hear(entity_t *e, game_t *g, const char *msg) {
  ent_brain_think_request_t *r =
      (ent_brain_think_request_t *)malloc(sizeof(ent_brain_think_request_t));
  r->game = g;
  r->entity = e;
  r->msg = msg;
  ent_brain_think_and_answer(r, cb_ent_think);
}
