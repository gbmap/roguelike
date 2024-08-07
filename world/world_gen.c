#include "world_gen.h"

void world_gen_grass(world_t *w) {
  for (int x = 0; x < w->size.x; x++) {
    for (int y = 0; y < w->size.y; y++) {
      const double sz = 15.0;
      double p = pnoise2d((((double)x) / w->size.x) * sz,
                          (((double)y) / w->size.y) * sz, 0.1, 2, 1338);
      if (p < 1.5) {
        entity_t e = {x, y, 0, ENT_MASK_VALID, "a"};
        world_spawn(w, e);
      }
    }
  }
}
