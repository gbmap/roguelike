#include "game.h"

#include "ui/speech_box.h"
#include "world/entity/player.h"
#include "world/world.h"
#include "world/world_gen.h"

#include "../termbox2/termbox2.h"

void draw_border() {
  for (int x = 0; x < tb_width(); x++) {
    tb_print(x, 0, 0, 0, "x");
    tb_print(x, tb_height() - 1, 0, 0, "x");
  }

  for (int y = 0; y < tb_height(); y++) {
    tb_print(0, y, 0, 0, "x");
    tb_print(tb_width() - 1, y, 0, 0, "x");
  }
}

void draw_debug(game_t *g) {
  tb_printf(0, g->term_w - 2, 0, 0, "world size=%d,%d", g->world->size.x,
            g->world->size.y);

  tb_printf(g->term_w - 16, g->term_h - 1, 0, 0, "|dt=%dms|", DELTA_TIME);
}

game_t *game_new() {
  game_t *g = (game_t *)malloc(sizeof(game_t));
  g->term_w = tb_width();
  g->term_h = tb_height();
  return g;
}

void game_init(game_t *g) {
  g->log = log_new();
  g->world = world_new(g->term_w, g->term_h, MAX_ENTITIES);
  g->player = player_init(g->world);

  world_gen_grass(g->world);
  g->is_running = 1;
}

void game_update(game_t *g, uint64_t dt) {
  struct tb_event ev;
  // event handling
  uint64_t t_pre_ev = time_ms();
  tb_peek_event(&ev, STEP_MS);
  uint64_t t_post_ev = time_ms();
  if ((t_post_ev - t_pre_ev) < STEP_MS) {
    usleep((t_post_ev - t_pre_ev) * 1000);
  }

  if (ev.type == TB_EVENT_KEY) {
    if (ev.ch == *"c") {
      entity_t e = {g->term_w / 2, g->term_h / 2, 1,
                    ENT_MASK_VALID | ENT_MASK_DYNAMIC, "☺"};
      world_spawn(g->world, e);
    } else if (ev.ch == *"l") {
      g->log->visible = 1 - g->log->visible;
    } else if (ev.ch == *"q") {
      g->is_running = 0;
    } else if (ev.ch == *"1") {
      STEP_MS = 200;
    } else if (ev.ch == *"2") {
      STEP_MS = 100;
    } else if (ev.ch == *"3") {
      STEP_MS = 50;
    } else if (ev.ch == *"s") {
      speech_push(&g->speech, "This is a message!", g->player);
    }
  }
  player_handle_event(g->player, ev);

  // logic
  world_update(g->world);
  speech_update(&g->speech, DELTA_TIME);
}

void game_draw(game_t *g) {
  // rendering
  tb_clear();
  world_draw(g->world);
  player_draw(g->player);
  speech_draw(&g->speech);
  draw_border();
  log_draw(g->log, g->term_w - 35, g->term_h - 19, 32, 16);
  draw_debug(g);
  tb_present();
}
