#define TB_IMPL
#include "../termbox2/termbox2.h"

#include "../game/world/entity/entity_brain.h"

void cb_ent_brain_think(ent_brain_think_request_t *r) {
  printf("%s", r->response);
}

void test_ent_think() {
  ent_brain_think_request_t r;
  r.msg = "This is a test.";
  r.game = 0;
  r.entity = 0;
  r.response = 0;
  ent_brain_think_and_answer(&r, cb_ent_brain_think);
}

int main(int argc, char *argv[]) {
  test_ent_think();
  return 0;
}
