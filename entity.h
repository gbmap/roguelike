#ifndef ENTITY__H
#define ENTITY__H

// ========================
//          ENTITY
// ========================
//

#define ENT_MASK_DYNAMIC 0b00000001
#define ENT_MASK_VALID 0b10000000

typedef struct {
  const char *name;
  float value;
} entity_stat_t;

typedef struct {
  const char *name;
  float value;
} entity_opinion_t;

typedef struct {
  int x;
  int y;
  int z;
  int mask;
  const char *symbol;
} entity_t;

extern entity_t ENT_INVALID;

void ent_draw(entity_t *e);
void ent_update(entity_t *e);

int ent_isvalid(entity_t *e);
int ent_isdynamic(entity_t *e);

void ent_destroy(entity_t *e);

#endif
