#include "ui.h"

#include "../../termbox2/termbox2.h"
#include "../d_world.h"
#include "../def.h"
#include "../g_entity.h"
#include "draw.h"
#include "speech_box.h"
#include "textbox.h"

textbox_t txtbox_say;

void ui_update(game_t *g, uint64_t dt) {
  if (g->state == GAME_STATE_WORLD) {
    speech_update(&g->speech, dt);
  }
}

void ui_handle_event(game_t *g, const struct tb_event ev) {
  if (ev.type != TB_EVENT_KEY) {
    return;
  }

  if (ev.key == KEY_CLOSE) {
    g->state = GAME_STATE_WORLD;
    return;
  }

  switch (g->state) {
  case GAME_STATE_ACTION:
    if (ev.ch == 's') {
      g->state = GAME_STATE_SAY;
    }
    break;
  case GAME_STATE_SAY:
    if (textbox_handle_event(&txtbox_say, ev)) {

      E_Say(g->world->player, g, "This is a message!");
      speech_push(&g->speech, txtbox_say.buffer, g->world->player);
      textbox_clear(&txtbox_say);
      g->state = GAME_STATE_WORLD;
    }
    break;
  }
}

void ui_draw(game_t *g) {
  speech_draw(&g->speech);
  ui_draw_log(g);

  switch (g->state) {
  case GAME_STATE_ACTION:
    ui_draw_action_menu(g);
    break;
  case GAME_STATE_SAY:
    ui_draw_action_menu(g);

    int twh = tb_width() / 2;
    int thh = tb_height() / 2;
    int w = tb_width() / 3;
    int h = tb_height() / 3;
    int x = twh - w / 2;
    int y = thh - h / 2;

    textbox_draw(&txtbox_say, x, y, w, h, g->dt);
    break;
  }

  ui_draw_border();
  ui_draw_menu(g);
  ui_draw_debug(g);
}

void ui_draw_menu(game_t *g) {
  tb_print(10, 0, 0, 0, " ACTIONS: | (space) action menu | ");
}

void ui_draw_action_menu(game_t *g) {
  int twh = tb_width() / 2;
  int thh = tb_height() / 2;
  int w = tb_width() / 3;
  int h = tb_height() / 3;
  int x = twh - w / 2;
  int y = thh - h / 2;

  U_DrawSquareFill(x, y, w, h, 0, "ACTIONS");

  x += 2;
  tb_print(x, y + 2, 0, 0, "(s) say");
  tb_print(x, y + 3, 0, 0, "(p) place");
  tb_print(x, y + 4, 0, 0, "(space) space");
}

void ui_draw_border() {
  for (int x = 0; x < tb_width(); x++) {
    tb_print(x, 0, 0, 0, "x");
    tb_print(x, tb_height() - 1, 0, 0, "x");
  }

  for (int y = 0; y < tb_height(); y++) {
    tb_print(0, y, 0, 0, "x");
    tb_print(tb_width() - 1, y, 0, 0, "x");
  }
}

void ui_draw_log(game_t *g) {
  log_t *l = g->log;
  if (!l->visible) {
    return;
  }

  int w = tb_width() / 3;
  int h = tb_height() - 4;
  int x = tb_width() - w - 3;
  int y = 2;

  U_DrawSquareFill(x, y, w, h, 0, "LOG");

  int sw = w - 3;
  for (int i = 0, lp = 0; i < h && lp < l->sz; lp++) {
    const char *msg = l->logs[abs((l->ptr - 1 - lp) % LOG_SIZE)];
    int msglen = strlen(msg);
    int x0 = 0;
    int x1 = sw;
    while (x0 < msglen && (y + i) < (y + h - 1)) {
      memset(&l->bfr_line, 0, BFR_LINE_SIZE);
      strncpy(&l->bfr_line, msg + x0, x1 - x0);
      tb_print(x + 2, y + 1 + i, 0, 0, l->bfr_line);
      i++;
      x0 = x1;
      x1 += sw;
      x1 = x1 > msglen ? msglen : x1;
    }
  }
}

void ui_draw_debug(game_t *g) {
  tb_printf(0, g->term_w - 2, 0, 0, "world size=%d,%d", g->world->size.x,
            g->world->size.y);

  tb_printf(g->term_w - 16, g->term_h - 1, 0, 0, "|dt=%dms|", DELTA_TIME);

  struct tb_event *ev = g->ev;
  tb_printf(2, g->term_h - 2, 0, 0, "|ev.type=%i|ev.key=%i|ev.ch=%i|", ev->type,
            ev->key, ev->ch);
}
