#ifndef __D_WORLD__
#define __D_WORLD__

#include <stdint.h>

//
// ENTITY
//

#define ENT_MASK_DYNAMIC 0b00000001
#define ENT_MASK_VALID 0b10000000
#define ENT_MASK_PLAYER 0b01000000

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

//
//  WORLD
//

typedef struct {
  int x;
  int y;
} v2i;

typedef struct {
  v2i size;

  entity_t *level;

  int max_entities;
  entity_t *entities;

  entity_t *player;
} world_t;

#define ENT_COLLECTION_MAX
typedef struct {
  entity_t *entities[64];
  uint32_t count;
} entity_collection_t;

#endif
