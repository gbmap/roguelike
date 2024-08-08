#include "world_gen.h"

void world_gen_grass(world_t *w) {
  for (int x = 0; x < w->size.x; x++) {
    for (int y = 0; y < w->size.y; y++) {
      const double sz = 15.0;
      double p1 = pnoise2d((((double)x) / w->size.x) * sz,
                           (((double)y) / w->size.y) * sz, 0.1, 2, 1338);

      double p2 = pnoise2d((((double)x) / w->size.x) * sz * 2,
                           (((double)y) / w->size.y) * sz * 2, 0.1, 5, 1338);
      if (p2 < -0.85) {
        entity_t e = {x, y, 0, ENT_MASK_VALID, "v"};
        world_spawn(w, e);
      } else if (p1 < 0.5) {
        entity_t e = {x, y, 0, ENT_MASK_VALID, "."};
        world_spawn(w, e);
      }
    }
  }
}
