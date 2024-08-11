
#define TB_IMPL
#include "termbox2/termbox2.h"

#include "game/game.h"

#define EVENT_POLL_TIMEOUT_MS 200

int main(int argc, char *argv[]) {
  tb_init();
  tb_set_input_mode(TB_INPUT_ESC);

  game_t *game = G_New();
  G_Init(game);

  struct tb_event ev;
  uint64_t ms0 = 0;
  while (game->is_running) {
    G_Update(game, DELTA_TIME);
    G_Draw(game);

    uint64_t ms1 = time_ms();
    DELTA_TIME = ms1 - ms0;
    ms0 = ms1;
  }
  tb_shutdown();

  return 0;
}
