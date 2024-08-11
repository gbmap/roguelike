#ifndef __D_UI__
#define __D_UI__

#define TEXTBOX_BFR_MAX_SIZE 2048

typedef struct {
  char buffer[TEXTBOX_BFR_MAX_SIZE];
  int cursor;
} textbox_t;

#endif
