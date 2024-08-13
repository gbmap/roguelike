#ifndef __D_CMD__
#define __D_CMD__

#include <stdint.h>

typedef void (*cmd_func_ptr)(void *);

typedef struct {
  uint32_t code;
  int tte;           // time to execution in world ticks
  cmd_func_ptr func; // command function
  void *data;        // parameters
  void *next;        // next cmd, buffer = linked list of commands
} cmd_t;

typedef cmd_t *cmd_buffer_t;

#endif
