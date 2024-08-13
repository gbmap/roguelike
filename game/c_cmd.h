
#ifndef __C_CMD__
#define __C_CMD__

#include "d_cmd.h"
#include "d_game.h"
#include "d_world.h"
#include "g_cmd.h"

#define CMD_WRLD_SPAWN 0
#define CMD_WRLD_KILL 1
#define CMD_ENT_MOVE 2
#define CMD_ENT_SAY 3
#define CMD_ENT_HEAR 4

typedef struct {
  entity_t *ent;
  int x;
  int y;
} cmd_ent_move_t;

typedef struct {
  game_t *game;
  entity_t *ent;
  const char *msg;
} cmd_ent_say_t;

typedef struct {
  game_t *game;
  entity_t *ent;
  line_t line;
} cmd_ent_hear_t;

void C_EntMove(void *data);
void C_EntSay(void *data);
void C_EntHear(void *data);

static const cmd_func_ptr CMD_LOOKUP[] = {0, 0, C_EntMove, C_EntSay, C_EntHear};

static const uint64_t CMD_DATA_SIZE_LOOKUP[] = {0, 0, sizeof(cmd_ent_move_t),
                                                sizeof(cmd_ent_say_t),
                                                sizeof(cmd_ent_hear_t)};

#endif
