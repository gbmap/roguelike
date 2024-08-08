
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

// void draw_debug(world_t *w, struct tb_event ev) {
//   tb_printf(0, TERM_H - 2, 0, 0, "world size=%d,%d", g_world->size.x,
//             g_world->size.y);
//   tb_printf(0, TERM_H - 1, 0, 0, "event type=%d key=%d ch=%c", ev.type,
//   ev.key,
//             ev.ch);
//
//   tb_printf(TERM_W - 16, TERM_H - 1, 0, 0, "|dt=%dms|", DELTA_TIME);
// }

int main(int argc, char *argv[]) {
  tb_init();
  TERM_W = tb_width();
  TERM_H = tb_height();

  game_t *game = game_new();
  game_init(game);

  // world_init(g_world);

  struct tb_event ev;
  uint64_t ms0 = 0;
  // while (1) {
  while (game->is_running) {
    // event handling
    // uint64_t t_pre_ev = time_ms();
    // tb_peek_event(&ev, STEP_MS);
    // uint64_t t_post_ev = time_ms();
    // if ((t_post_ev - t_pre_ev) < STEP_MS) {
    //   usleep((t_post_ev - t_pre_ev) * 1000);
    // }

    // if (ev.type == TB_EVENT_KEY) {
    //   if (ev.ch == *"c") {
    //     entity_t e = {TERM_W / 2, TERM_H / 2, 1,
    //                   ENT_MASK_VALID | ENT_MASK_DYNAMIC, "☺"};
    //     world_spawn(g_world, e);
    //   } else if (ev.ch == *"l") {
    //     g_log->visible = 1 - g_log->visible;
    //   } else if (ev.ch == *"q") {
    //     break;
    //   } else if (ev.ch == *"1") {
    //     STEP_MS = 200;
    //   } else if (ev.ch == *"2") {
    //     STEP_MS = 100;
    //   } else if (ev.ch == *"3") {
    //     STEP_MS = 50;
    //   } else if (ev.ch == *"s") {
    //     // speech_push(&g_speech, "This is a message!",
    //     &g_world->entities[0]);
    //   }
    // }
    // player_handle_event(g_player, ev);

    // // logic
    // world_update(g_world);
    // speech_update(&g_speech, DELTA_TIME);
    //

    game_update(game, DELTA_TIME);
    game_draw(game);

    uint64_t ms1 = time_ms();
    DELTA_TIME = ms1 - ms0;
    ms0 = ms1;
  }
  tb_shutdown();

  return 0;
}
