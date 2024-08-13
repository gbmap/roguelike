#ifndef __U_LOG__
#define __U_LOG__

#include "d_game.h"

log_t *log_new();
void log_msg(log_t *l, const char *msg);
void log_msgf(log_t *l, const char *format, ...);
void log_draw(log_t *l, int x, int y, int w, int h);

#endif
