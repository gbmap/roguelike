#ifndef __D_GAME__
#define __D_GAME__

#include <stdint.h>

#include "d_world.h"
#include "time.h"

//
//  LOGGING
//

#define LOG_SIZE 16
#define LOG_ENTRY_MAX_SIZE 1024
#define BFR_LINE_SIZE 1024

typedef struct {
  char *logs[LOG_SIZE];
  int ptr;
  int sz;
  int visible;

  char bfr_line[BFR_LINE_SIZE]; // used to draw overflown lines
} log_t;

//
//   SPEECH
//

#define SPEECH_BOX_MSG_SIZE 256
#define SPEECH_BOX_W 22
#define SPEECH_BOX_H 4
#define SPEECH_BOX_TIME 5000

typedef struct {
  char msg[SPEECH_BOX_MSG_SIZE];
  int visible;
  int time;
  entity_t *ent;
} speech_box_t;

#define SPEECH_BFR_SIZE 128

typedef struct {
  speech_box_t speech_boxes[SPEECH_BFR_SIZE];
} speech_t;

//
// GAME
//

#include "d_ui.h"
#include "d_world.h"

#define MAX_ENTITIES 1024 * 1024

#define GAME_STATE_WORLD 0
#define GAME_STATE_ACTION 1
#define GAME_STATE_SAY 2
#define GAME_STATE_PLACE 2

typedef uint32_t game_state_t;

struct tb_event;

typedef struct {
  int term_w, term_h;
  int is_running;
  uint64_t dt;
  game_state_t state;

  struct tb_event *ev;

  world_t *world;
  log_t *log;
  speech_t speech;
} game_t;

#endif
