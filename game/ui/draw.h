#ifndef DRAW__H
#define DRAW__H

typedef struct {
  int fg;
  int bg;
  const char *h;
  const char *v;
  const char *ul;
  const char *ur;
  const char *bl;
  const char *br;
} cfg_square_t;

extern const cfg_square_t CFG_DEFAULT_SQR;

void draw_square(int x, int y, int w, int h, const cfg_square_t *c);

void draw_square_fill(int x, int y, int w, int h, const cfg_square_t *c);

void U_DrawSquareFill(int x, int y, int w, int h, const cfg_square_t *c,
                      const char *title);

void draw_textbox(int x, int y, int w, int h, const char *msg,
                  const cfg_square_t *c);

#endif
