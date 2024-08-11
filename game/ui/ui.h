#ifndef UI__H
#define UI__H

#include "../d_game.h"
#include "../log.h"
#include <stdint.h>

struct tb_event;

#define TEXTBOX_BFR_MAX_SIZE 2048

extern textbox_t txtbox_say;

void ui_update(game_t *g, uint64_t dt);
void ui_handle_event(game_t *g, const struct tb_event ev);
void ui_draw(game_t *g);
void ui_draw_menu(game_t *g);
void ui_draw_action_menu(game_t *g);
void ui_draw_border();
void ui_draw_log(game_t *g);
void ui_draw_debug(game_t *g);

#endif
