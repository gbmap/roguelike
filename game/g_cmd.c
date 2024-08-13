#include "g_cmd.h"
#include "d_cmd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_cmd.h"

cmd_buffer_t cmdbuffer = 0;

cmd_t *C_New(uint32_t code, int tte, cmd_func_ptr func, void *data,
             int datasz) {
  cmd_t *cmd = (cmd_t *)malloc(sizeof(cmd_t));
  cmd->tte = tte;
  cmd->code = code;
  cmd->func = func;
  cmd->data = (void *)malloc(datasz);
  memcpy(cmd->data, data, datasz);

  cmd->next = 0;
  return cmd;
}

void C_Free(cmd_t *c) {
  free(c->data);
  free(c);
  c = 0;
}

void C_PushCmd(cmd_t *cmd, cmd_buffer_t *bfr) {
  if (*bfr == 0) {
    *bfr = &(*cmd);
    return;
  }

  cmd_t *last = *bfr;
  while (last->next) {
    last = last->next;
  }
  last->next = cmd;
}

void C_Push(uint32_t cmdcode, uint32_t tte, void *data) {
  C_PushCmd(C_New(cmdcode, tte, CMD_LOOKUP[cmdcode], data,
                  CMD_DATA_SIZE_LOOKUP[cmdcode]),
            &cmdbuffer);
}

void C_RecurseExecute(cmd_t **prev, cmd_t **cur) {
  if ((*cur)->tte > 0) {
    (*cur)->tte--;
    C_RecurseExecute(cur, (cmd_t **)&((*cur)->next));
  } else {
    (*cur)->func((*cur)->data);
    if (*prev) {
      (*prev)->next = (*cur)->next;
    } else { // first node, advance root cmd pointer
      cur = (cmd_t **)&((*cur))->next;
    }
  }
}

void C_BufferUpdate(cmd_buffer_t *bfr, uint64_t dt) {
  for (cmd_t *prev = 0, *cur = *bfr; cur;) {
    if (cur->tte > 0) {
      cur->tte--;
      prev = cur;
      cur = cur->next;
      continue;
    }

    cur->func(cur->data);
    cmd_t *next = cur->next;
    if (prev) {
      prev->next = next;
    } else {
      *bfr = (cmd_t *)(*bfr)->next;
    } // no previous ptr means root cmd

    C_Free(cur);
    cur = next;
  }
}
