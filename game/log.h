#ifndef LOG__H
#define LOG__H

#define LOG_SIZE 16
#define LOG_ENTRY_MAX_SIZE 1024
#define BFR_LINE_SIZE 1024

typedef struct {
  char *logs[LOG_SIZE];
  int ptr;
  int sz;
  int visible;

  char bfr_line[BFR_LINE_SIZE]; // used to draw overflown lines
} log_t;

log_t *log_new();
void log_msg(log_t *l, const char *msg);
void log_msgf(log_t *l, const char *format, ...);
void log_draw(log_t *l, int x, int y, int w, int h);

#endif
