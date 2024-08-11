#ifndef ENTITY__H
#define ENTITY__H

// ========================
//          ENTITY
// ========================
//

#define ENT_MASK_DYNAMIC 0b00000001
#define ENT_MASK_VALID 0b10000000
#define ENT_MASK_PLAYER 0b01000000

#include "../../d_game.h"

extern entity_t ENT_INVALID;

void ent_draw(entity_t *e);
void ent_update(entity_t *e);

int ent_isvalid(entity_t *e);
int ent_isdynamic(entity_t *e);

void ent_destroy(entity_t *e);

void ent_say(entity_t *e, game_t *g, const char *msg);
void ent_hear(entity_t *e, game_t *g, const char *msg);

#endif
