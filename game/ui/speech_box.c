#include "speech_box.h"

#include "../ui/draw.h"
#include <stdlib.h>

void speech_box_reset(speech_box_t *s, char *msg, entity_t *ent) {
  s->msg = msg;
  s->visible = 1;
  s->time = 0;
  s->ent = ent;
}

speech_box_t *speech_box_new(char *msg, entity_t *ent) {
  speech_box_t *s = (speech_box_t *)malloc(sizeof(speech_box_t));
  speech_box_reset(s, msg, ent);
  return s;
}

void speech_box_update(speech_box_t *s, int dt) {
  if (!s->visible) {
    return;
  }

  s->time += dt;
  if (s->time > SPEECH_BOX_TIME) {
    s->visible = 0;
  }
}

void speech_box_draw(speech_box_t *s) {
  if (!s->visible) {
    return;
  }
  draw_textbox(s->ent->x - SPEECH_BOX_W / 2, s->ent->y - SPEECH_BOX_H - 2,
               SPEECH_BOX_W, SPEECH_BOX_H, s->msg, &CFG_DEFAULT_SQR);
}

// ===================
//    SPEECH
//

void speech_update(speech_t *s, uint64_t dt) {
  for (int i = 0; i < SPEECH_BFR_SIZE; i++) {
    speech_box_t *b = &s->speech_boxes[i];
    if (!b->visible) {
      continue;
    }
    speech_box_update(b, dt);
  }
}

void speech_draw(speech_t *s) {
  for (int i = 0; i < SPEECH_BFR_SIZE; i++) {
    speech_box_t *b = &s->speech_boxes[i];
    if (!b->visible) {
      continue;
    }
    speech_box_draw(b);
  }
}

void speech_push(speech_t *s, char *msg, entity_t *ent) {
  for (int i = 0; i < SPEECH_BFR_SIZE; i++) {
    speech_box_t *b = &s->speech_boxes[i];
    if (b->visible) {
      continue;
    }
    speech_box_reset(b, msg, ent);
  }
}
