#ifndef SPEECH_BOX__H
#define SPEECH_BOX__H

#include "../d_game.h"

speech_box_t *speech_box_new(char *msg, entity_t *ent);
void speech_box_reset(speech_box_t *s, const char *msg, entity_t *ent);
void speech_box_update(speech_box_t *s, int dt);
void speech_box_draw(speech_box_t *s);

// ====================
//      SPEECH
//

void speech_update(speech_t *s, uint64_t dt);
void speech_draw(speech_t *s);
void speech_push(speech_t *s, const char *msg, entity_t *ent);

#endif
