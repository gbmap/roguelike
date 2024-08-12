#include "g_entity.h"
#include "../termbox2/termbox2.h"
#include "d_world.h"
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
int E_IsValid(entity_t *e) { return (e->mask & ENT_MASK_VALID) > 1; }
int E_IsDynamic(entity_t *e) { return e->mask & ENT_MASK_DYNAMIC; }
void E_Kill(entity_t *e) { e->mask = 0; }

// ============
//
//

void E_Say(entity_t *e, game_t *g, const char *msg) {
  speech_push(&g->speech, msg, e);

  line_t l = {e->name, msg, 0};
  E_DialoguePush(e->dialogue, l);

  entity_collection_t ents_heard = world_get_entities(g->world, e->x, e->y, 10);
  for (int i = 0; i < ents_heard.count; i++) {
    entity_t *eh = ents_heard.entities[i];
    if (eh == e) {
      continue;
    }

    E_Hear(eh, g, l);
  }
}

void cb_ent_think(ent_brain_think_request_t *r) {
  speech_push(&r->game->speech, r->response, r->entity);
  free(r);
}

void E_Hear(entity_t *e, game_t *g, line_t l) {
  E_DialoguePush(e->dialogue, l);

  ent_brain_think_request_t *r =
      (ent_brain_think_request_t *)malloc(sizeof(ent_brain_think_request_t));
  r->game = g;
  r->entity = e;
  r->msg = l.line;
  ent_brain_think_and_answer(r, cb_ent_think);
}

opinion_collection_t E_NewOpinionCollection() {
  opinion_t INVALID = {"\0", 0.0};
  opinion_collection_t c;
  for (int i = 0; i < ENT_MAX_OPINIONS; i++) {
    c.opinions[i] = INVALID;
  }
  return c;
}

line_t *E_DialoguePush(line_t *dialogue, line_t l) {
  line_t *line = (line_t *)malloc(sizeof(line_t));
  line->name = l.name;
  line->line = l.line;
  line->next = 0;

  if (!dialogue) {
    return line;
  }

  int count = 0;
  line_t *first = dialogue;
  line_t *last = first;
  while (last->next) {
    last = last->next;
    count++;
  }

  if (count > ENT_MAX_DIALOGUE_LEN) {
    line_t *tmp = first;
    first = first->next;
    free((void *)tmp->line);
    free(tmp);
  }

  last->next = line;
  return first;
}
