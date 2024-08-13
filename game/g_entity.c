#include "g_entity.h"
#include "../termbox2/termbox2.h"
#include "d_world.h"
#include "u_str.h"

#include "c_cmd.h"
#include "g_cmd.h"
#include "u_rand.h"

entity_t ENT_INVALID = {-1, -1, -1, 0, "\0"};

entity_t E_New(const char *name, entity_repr_t *repr, int mask) {
  entity_t e;
  e.name = name;
  e.symbol = repr->symbol;
  e.mask = ENT_MASK_VALID | mask;

  e.dialogue = 0;
  e.opinions = E_NewOpinionCollection();
  return e;
}

// entities are buffered in world, so just
// mask it as invalid.
void E_Kill(entity_t *e) { e->mask = 0; }

void E_Update(entity_t *e) {
  if (e->mask & ENT_MASK_PLAYER) {
    return;
  }

  if (e->mask & ENT_MASK_DYNAMIC) {
    int d = rand() % 2 == 0 ? -1 : 1;
    int x = e->x;
    int y = e->y;
    if (rand() % 2 == 0) {
      x += d;
    } else {
      y += d;
    }

    cmd_ent_move_t cmd_move = {e, x, y};
    C_Push(CMD_ENT_MOVE, 0, &cmd_move);
  }
}

void E_Draw(entity_t *e) { tb_print(e->x, e->y, 0, 0, e->symbol); }
int E_IsValid(entity_t *e) { return (e->mask & ENT_MASK_VALID) > 1; }
int E_IsDynamic(entity_t *e) { return e->mask & ENT_MASK_DYNAMIC; }

// ============
//
//

void E_Say(entity_t *e, game_t *g, const char *msg) {
  cmd_ent_say_t cmd = {g, e, strcopy(msg)};
  C_Push(CMD_ENT_SAY, 0, &cmd);
}

void E_Hear(entity_t *e, game_t *g, line_t l) {
  cmd_ent_hear_t cmd = {g, e, l};
  C_Push(CMD_ENT_HEAR, rand() % 4, &cmd);
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
