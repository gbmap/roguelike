#ifndef __G_CMD__
#define __G_CMD__

#include "d_cmd.h"

extern cmd_buffer_t cmdbuffer;

cmd_t *C_New(uint32_t code, int tte, cmd_func_ptr func, void *data, int datasz);
void C_PushCmd(cmd_t *cmd, cmd_buffer_t *bfr);
void C_Push(uint32_t cmdcode, uint32_t tte, void *data);
void C_BufferUpdate(cmd_buffer_t *bfr, uint64_t dt);

#endif
