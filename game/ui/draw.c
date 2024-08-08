#include "draw.h"

#include "../../termbox2/termbox2.h"

const cfg_square_t CFG_DEFAULT_SQR = {0, 0, "-", "|", ".", ".", ".", "."};

void draw_square(int x, int y, int w, int h, const cfg_square_t *c) {
  for (int rx = 1; rx < w; rx++) {
    tb_print(x + rx, y, c->fg, c->bg, c->h);
    tb_print(x + rx, y + h, c->fg, c->bg, c->h);
  }

  for (int ry = 0; ry < h; ry++) {
    tb_print(x, y + ry, c->fg, c->bg, c->v);
    tb_print(x + w, y + ry, c->fg, c->bg, c->v);
  }
  tb_print(x, y, c->fg, c->bg, c->ul);
  tb_print(x + w, y, c->fg, c->bg, c->ur);
  tb_print(x, y + h, c->fg, c->bg, c->bl);
  tb_print(x + w, y + h, c->fg, c->bg, c->br);
}

void draw_square_fill(int x, int y, int w, int h, const cfg_square_t *c) {
  if (c == 0) {
    c = &CFG_DEFAULT_SQR;
  }
  draw_square(x, y, w, h, c);
  for (int ry = 1; ry < h; ry++) {
    for (int rx = 1; rx < w; rx++) {
      tb_print(x + rx, y + ry, c->fg, c->bg, " ");
    }
  }
}

void draw_textbox(int x, int y, int w, int h, const char *msg,
                  const cfg_square_t *c) {
  if (c == 0) {
    c = &CFG_DEFAULT_SQR;
  }

  draw_square_fill(x, y, w, h, c);
  int rx = x + 2;
  int ry = y + 1;
  for (int i = 0; i < strlen(msg); i++) {
    if (rx > (x + w - 2)) {
      rx = x + 2;
      ry++;
      if (ry > (y + h - 1)) {
        return;
      }
    }

    char ch[2] = {*(msg + i), '\0'};
    tb_print(rx++, ry, c->fg, c->bg, &ch);
  }
}
