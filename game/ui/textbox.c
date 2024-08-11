#include "textbox.h"

#include "../../termbox2/termbox2.h"

#include "draw.h"

void textbox_push(textbox_t *t, char c) {
  t->buffer[t->cursor++] = c;
  t->buffer[t->cursor] = '\0';
}

void textbox_pop(textbox_t *t) { t->buffer[t->cursor--] = '\0'; }

void textbox_clear(textbox_t *t) {
  t->cursor = 0;
  memset(&t->buffer, '\0', strlen(t->buffer));
}

int textbox_handle_event(textbox_t *t, const struct tb_event ev) {
  if (ev.type != TB_EVENT_KEY) {
    return 0;
  }

  if (ev.key == TB_KEY_BACKSPACE || ev.key == TB_KEY_BACKSPACE2) {
    textbox_pop(t);
  } else if (ev.key == TB_KEY_ENTER) {
    return 1;
  } else {
    textbox_push(t, ev.ch);
  }
  return 0;
}

void textbox_draw(textbox_t *t, int x, int y, int w, int h, uint64_t dt) {
  draw_textbox(x, y, w, h, &t->buffer, 0);
}
