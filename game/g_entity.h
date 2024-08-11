#ifndef ENTITY__H
#define ENTITY__H

// ========================
//          ENTITY
// ========================
//

#define ENT_MASK_DYNAMIC 0b00000001
#define ENT_MASK_VALID 0b10000000
#define ENT_MASK_PLAYER 0b01000000

#include "d_game.h"

extern entity_t ENT_INVALID;


void E_Draw(entity_t* e);
void E_Update(entity_t* e);

int E_IsValid(entity_t* e);
int E_IsDynamic(entity_t *e);

void E_Kill(entity_t *e);

void ent_say(entity_t *e, game_t *g, const char *msg);
void ent_hear(entity_t *e, game_t *g, const char *msg);

#endif
