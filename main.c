
// #include "player.h"
#include <time.h>

#define TB_IMPL
#include "termbox2/termbox2.h"

// #include "entity/entity.h"
#include "game/game.h"
// #include "log.h"
// #include "player.h"
// #include "time.h"
// #include "ui/speech_box.h"
// #include "world/world.h"
// #include "world/world_gen.h"

#define EVENT_POLL_TIMEOUT_MS 200

int TERM_W = -1;
int TERM_H = -1;

// world_t *g_world = 0;
// log_t *g_log = 0;
// speech_t g_speech;

int main(int argc, char *argv[]) {
  tb_init();
  TERM_W = tb_width();
  TERM_H = tb_height();

  game_t *game = game_new();
  game_init(game);

  // world_init(g_world);

  struct tb_event ev;
  uint64_t ms0 = 0;
  while (game->is_running) {
    game_update(game, DELTA_TIME);
    game_draw(game);

    uint64_t ms1 = time_ms();
    DELTA_TIME = ms1 - ms0;
    ms0 = ms1;
  }
  tb_shutdown();

  return 0;
}
