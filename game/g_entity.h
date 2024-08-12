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

void E_Draw(entity_t *e);
void E_Update(entity_t *e);

int E_IsValid(entity_t *e);
int E_IsDynamic(entity_t *e);

void E_Kill(entity_t *e);

void E_Say(entity_t *e, game_t *g, const char *msg);
void E_Hear(entity_t *e, game_t *g, line_t l);

line_t *E_DialoguePush(line_t *e, line_t l);

opinion_collection_t E_NewOpinionCollection();

#endif
