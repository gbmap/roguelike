#ifndef TEXTBOX__H
#define TEXTBOX__H

#include "../d_game.h"

void textbox_push(textbox_t *t, char c);
void textbox_pop(textbox_t *t);
void textbox_clear(textbox_t *t);
int textbox_handle_event(textbox_t *t, const struct tb_event ev);
void textbox_draw(textbox_t *t, int x, int y, int w, int h, uint64_t dt);

#endif
