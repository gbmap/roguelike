#include "u_log.h"

#include "../termbox2/termbox2.h"
#include "ui/draw.h"
#include <string.h>

log_t *log_new() {
  log_t *l = (log_t *)malloc(sizeof(log_t));
  for (int i = 0; i < LOG_SIZE; i++) {
    l->logs[i] = (char *)malloc(sizeof(char) * LOG_ENTRY_MAX_SIZE);
  }
  l->ptr = 0;
  l->sz = 0;
  return l;
}

void log_msg(log_t *l, const char *msg) {
  int msglen = strlen(msg);
  int cpsz = msglen > LOG_ENTRY_MAX_SIZE ? LOG_ENTRY_MAX_SIZE : msglen;
  memcpy(l->logs[l->ptr], msg, cpsz);
  l->ptr = (l->ptr + 1) % LOG_SIZE;
  l->sz = (l->sz + 1) < LOG_SIZE ? l->sz + 1 : LOG_SIZE;
}

void log_msgf(log_t *l, const char *format, ...) {
  va_list arg_list;
  va_start(arg_list, format);
  vsprintf(l->logs[l->ptr], format, arg_list);
  log_msg(l, l->logs[l->ptr]);
}

void log_draw(log_t *l, int x, int y, int w, int h) {
  if (!l->visible) {
    return;
  }

  draw_square_fill(x, y, w, h, 0);

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
