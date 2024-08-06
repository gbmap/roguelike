#include "entity.h"
#define TB_IMPL

#include <time.h>

#include "termbox2/termbox2.h"

#include "world/world.h"
#include "world/world_gen.h"

#define MAX_ENTITIES 1024 * 1024

int TERM_W = -1;
int TERM_H = -1;

world_t *g_world = 0;

void world_init(world_t *w) {
  entity_t e = {TERM_W / 2, TERM_H / 2, 1, ENT_MASK_VALID | ENT_MASK_DYNAMIC,
                "☺"};
  world_spawn(w, e);
  world_gen_grass(g_world);

  entity_t el = {TERM_W / 2, TERM_H / 2, 1, ENT_MASK_VALID, "v"};
  world_spawn_level(w, el);
}

void draw_border() {
  for (int x = 0; x < TERM_W; x++) {
    tb_print(x, 0, 0, 0, "x");
    tb_print(x, TERM_H - 1, 0, 0, "x");
  }

  for (int y = 0; y < TERM_H; y++) {
    tb_print(0, y, 0, 0, "x");
    tb_print(TERM_W - 1, y, 0, 0, "x");
  }
}

int main(int argc, char *argv[]) {
  tb_init();

  TERM_W = tb_width();
  TERM_H = tb_height();

  g_world = world_new(TERM_W, TERM_H, MAX_ENTITIES);
  world_init(g_world);

  struct tb_event ev;
  while (!(ev.type == TB_EVENT_KEY && ev.ch == *"q")) {
    clock_t t0 = clock();

    tb_clear();

    // even handling
    tb_peek_event(&ev, 100);
    if (ev.type == TB_EVENT_KEY && ev.ch == *"c") {
      entity_t e = {TERM_W / 2, TERM_H / 2, 1,
                    ENT_MASK_VALID | ENT_MASK_DYNAMIC, "☺"};
      world_spawn(g_world, e);
    }

    world_update(g_world);

    // rendering
    world_draw(g_world);
    draw_border();
    tb_printf(0, TERM_H - 2, 0, 0, "world size=%d,%d", g_world->size.x,
              g_world->size.y);
    tb_printf(0, TERM_H - 1, 0, 0, "event type=%d key=%d ch=%c", ev.type,
              ev.key, ev.ch);

    entity_t e = {TERM_W / 2, TERM_H / 2, 1, ENT_MASK_VALID | ENT_MASK_DYNAMIC,
                  "☺"};
    // tb_printf(0, TERM_H - 3, 0, 0,
    //           "valid=%d, valid_ent=%d, ent_dyn=%d, mask=%d",
    //           (ENT_INVALID.mask & ENT_MASK_VALID) == 1,
    //           (e.mask & ENT_MASK_VALID) == 1, e.mask & ENT_MASK_DYNAMIC);
    tb_printf(0, TERM_H - 3, 0, 0, "symbol=%v",
              world_get_entity(g_world, TERM_W / 2, TERM_H / 2, ENT_MASK_VALID)
                  ->symbol);

    clock_t t1 = clock();
    int ms = (int)(((double)(t1 - t0) / CLOCKS_PER_SEC) * 1000);
    tb_printf(TERM_W - 16, TERM_H - 1, 0, 0, "|time=%dms|", ms);
    tb_present();
  }
  tb_shutdown();

  return 0;
}
