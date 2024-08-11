#ifndef __D_CMD__
#define __D_CMD__

#include <stdint.h>

#define CMD_WRLD_SPAWN 1000
#define CMD_WRLD_KILL 1001

#define CMD_LOG 50

#define CMD_BUFFER_SIZE 1024

typedef struct {
  uint32_t command;
  void *param;
} cmd_t;

typedef struct {
  cmd_t *buffer[CMD_BUFFER_SIZE];
} cmd_buffer_t;

#endif
