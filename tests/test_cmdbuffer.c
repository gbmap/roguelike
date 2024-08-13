
#define TB_IMPL
#include "../termbox2/termbox2.h"

#include "../game/g_cmd.h"

void cmd_exec(void *data) {
  const char *msg = (const char *)data;
  printf("%s", msg);
}

int main(int argc, char *argv[]) {

  printf("\n=======================\n");

  cmd_t *cmd =
      C_New(0, 10, cmd_exec, "This should be the second message.\n", 0);
  C_Push(cmd, &cmdbuffer);
  printf("cmdbuffer tte: %d\n", cmdbuffer->tte);

  cmd_t *cmd2 = C_New(0, 5, cmd_exec, "This should be the first message.\n", 0);
  C_Push(cmd2, &cmdbuffer);

  cmd_t *cmd3 = C_New(0, -100, cmd_exec, "This should be immediate.\n", 0);
  C_Push(cmd3, &cmdbuffer);

  for (int i = 0; i < 20; i++) {
    printf("%d)", i);
    C_BufferUpdate(&cmdbuffer, 0);
  }

  printf("\n=======================\n");
  return EXIT_SUCCESS;
}
