#include "speech_box.h"

#include "../ui/draw.h"
#include <stdlib.h>
#include <string.h>

void speech_box_reset(speech_box_t *s, const char *msg, entity_t *ent) {
  int msglen = strlen(msg);
  msglen = msglen > SPEECH_BOX_MSG_SIZE ? SPEECH_BOX_MSG_SIZE : msglen;
  memset(&s->msg, '\0', SPEECH_BOX_MSG_SIZE);
  strncpy(&s->msg, msg, msglen);
  s->msg[SPEECH_BOX_MSG_SIZE - 1] = '\0';
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

  int n = strlen(s->msg);
  int h = n / SPEECH_BOX_W;
  h = (h ? h : 1) + 1;

  int w = (n < SPEECH_BOX_W ? n : SPEECH_BOX_W) + 4;

  draw_textbox(s->ent->x - w / 2, s->ent->y - h - 2, w, h, s->msg,
               &CFG_DEFAULT_SQR);
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

void speech_push(speech_t *s, const char *msg, entity_t *ent) {
  speech_box_t *b = 0;
  for (int i = 0; i < SPEECH_BFR_SIZE; i++) {
    speech_box_t *bi = &s->speech_boxes[i];
    if (bi->visible && bi->ent == ent) {
      b = bi;
      break;
    } else if (!bi->visible) {
      b = bi;
      continue;
    }
  }

  if (b) {
    speech_box_reset(b, msg, ent);
  }
}
