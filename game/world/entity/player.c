#include "player.h"

#include "../../../termbox2/termbox2.h"
#include "../world.h"

entity_t *g_player = 0;

entity_t *player_init(world_t *w) {
  entity_t p = {128, 32, 0, ENT_MASK_VALID | ENT_MASK_DYNAMIC | ENT_MASK_PLAYER,
                "☺"};
  g_player = world_spawn(w, p);
  return g_player;
}

void player_handle_event(entity_t *p, const struct tb_event ev) {
  if (ev.type != TB_EVENT_KEY) {
    return;
  }

  if (ev.ch == *"s") {
    p->y += 1;
  } else if (ev.ch == *"w") {
    p->y -= 1;
  } else if (ev.ch == *"a") {
    p->x -= 1;
  } else if (ev.ch == *"d") {
    p->x += 1;
  }
}

void player_draw(entity_t *p) {
  tb_print(p->x, p->y, TB_GREEN | TB_BRIGHT, 0, p->symbol);
}
