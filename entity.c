#include "entity.h"
#include "termbox2/termbox2.h"
#include <string.h>

entity_t ENT_INVALID = {-1, -1, -1, 0, "\0"};

void ent_update(entity_t *e) {
  if (e->mask & ENT_MASK_DYNAMIC) {
    int d = rand() % 2 == 0 ? -1 : 1;
    if (rand() % 2 == 0) {
      e->x += d;
    } else {
      e->y += d;
    }
  }
}
void ent_draw(entity_t *e) { tb_print(e->x, e->y, 0, 0, e->symbol); }

int ent_isvalid(entity_t *e) { return (e->mask & ENT_MASK_VALID) > 1; }
int ent_isdynamic(entity_t *e) { return e->mask & ENT_MASK_DYNAMIC; }
void ent_destroy(entity_t *e) { e->mask = 0; }
