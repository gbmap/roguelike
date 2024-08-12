#ifndef __D_WORLD__
#define __D_WORLD__

#include <stdint.h>

//
//   OPINIONS
//

#define ENT_MAX_OPINIONS 32

typedef struct {
  const char *name;
  float value;
} opinion_t;

typedef struct {
  opinion_t opinions[ENT_MAX_OPINIONS];
} opinion_collection_t;

//
//  DIALOGUE
//

#define ENT_MAX_DIALOGUE_LEN 32

typedef struct {
  const char *name;
  const char *line;
  void *next;
} line_t;

//
// ENTITY
//

#define ENT_MASK_DYNAMIC 0b00000001
#define ENT_MASK_VALID 0b10000000
#define ENT_MASK_PLAYER 0b01000000

#define ENT_MAX_NAME_SZ 128
#define ENT_MAX_OPINION_NAME_SZ 128 // with ": " in the middle and \n suffix
#define ENT_MAX_OPINION_DEC_SZ 5    // 3 decimal places + 0.

typedef struct {
  const char *name;
  float value;
} entity_stat_t;

typedef struct {
  int x;
  int y;
  int z;
  int mask;
  const char *symbol;

  const char *name;
  line_t *dialogue; // history of things the entity remembers hearing
  opinion_collection_t opinions;
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
