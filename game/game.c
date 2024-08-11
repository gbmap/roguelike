#include "game.h"

#include "ui/ui.h"
#include "world/entity/player.h"
#include "world/world.h"
#include "world/world_gen.h"

#include "../termbox2/termbox2.h"

game_t *G_New() {
  game_t *g = (game_t *)malloc(sizeof(game_t));
  g->term_w = tb_width();
  g->term_h = tb_height();
  return g;
}

void G_Init(game_t *g) {
  g->log = log_new();

  g->world = world_new(g->term_w, g->term_h, MAX_ENTITIES);
  g->world->player = player_init(g->world);
  world_gen_grass(g->world);

  g->is_running = 1;
}

struct tb_event ev;
void G_Update(game_t *g, uint64_t dt) {
  g->dt = dt;

  // event handling
  uint64_t t_pre_ev = time_ms();
  tb_peek_event(&ev, STEP_MS);
  uint64_t t_post_ev = time_ms();
  if ((t_post_ev - t_pre_ev) < STEP_MS) {
    usleep((t_post_ev - t_pre_ev) * 1000);
  }
  g->ev = &ev;

  switch (g->state) {
  case GAME_STATE_WORLD:
    if (ev.type == TB_EVENT_KEY) {
      if (ev.ch == *"c") {
        entity_t e = {g->term_w / 2, g->term_h / 2, 1,
                      ENT_MASK_VALID | ENT_MASK_DYNAMIC, "☺"};
        world_spawn(g->world, e);
      } else if (ev.ch == *"l") {
        g->log->visible = 1 - g->log->visible;
      } else if (ev.ch == *"1") {
        STEP_MS = 200;
      } else if (ev.ch == *"2") {
        STEP_MS = 100;
      } else if (ev.ch == *"3") {
        STEP_MS = 50;
      } else if (ev.ch == TB_KEY_SPACE) {
        g->state = GAME_STATE_ACTION;
      } else if (ev.ch == *"q") {
        g->is_running = 0;
        return;
      }
    }
    player_handle_event(g->world->player, ev);
    world_update(g->world);
    break;
  case GAME_STATE_ACTION:
  case GAME_STATE_SAY:
    ui_handle_event(g, ev);
    break;
  }

  // logic
  ui_update(g, DELTA_TIME);
}

void G_Draw(game_t *g) {
  // rendering
  tb_clear();
  world_draw(g->world);
  ui_draw(g);
  tb_present();
}
