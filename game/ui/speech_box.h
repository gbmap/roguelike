#ifndef SPEECH_BOX__H
#define SPEECH_BOX__H

#include "../time.h"
#include "../world/entity/entity.h"

#define SPEECH_BOX_MSG_SIZE 256
#define SPEECH_BOX_W 22
#define SPEECH_BOX_H 4
#define SPEECH_BOX_TIME 5000

typedef struct {
  char *msg;
  int visible;
  int time;
  entity_t *ent;
} speech_box_t;

speech_box_t *speech_box_new(char *msg, entity_t *ent);
void speech_box_reset(speech_box_t *s, char *msg, entity_t *ent);
void speech_box_update(speech_box_t *s, int dt);
void speech_box_draw(speech_box_t *s);

// ====================
//      SPEECH
//
#define SPEECH_BFR_SIZE 128 // number of speech boxes in speech_t buffer

typedef struct {
  speech_box_t speech_boxes[SPEECH_BFR_SIZE];
} speech_t;

void speech_update(speech_t *s, uint64_t dt);
void speech_draw(speech_t *s);
void speech_push(speech_t *s, char *msg, entity_t *ent);

#endif
