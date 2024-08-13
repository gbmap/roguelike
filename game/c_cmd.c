#include "c_cmd.h"

#include "g_entity.h"
#include "g_world.h"
#include "ui/speech_box.h"
#include "world/entity/entity_brain.h"
#include <stdlib.h>

void C_EntMove(void *data) {
  cmd_ent_move_t *cmd = (cmd_ent_move_t *)data;
  cmd->ent->x = cmd->x;
  cmd->ent->y = cmd->y;
}

void C_EntSay(void *data) {
  cmd_ent_say_t *cmd = data;
  speech_push(&cmd->game->speech, cmd->msg, cmd->ent);

  line_t l = {cmd->ent->name, cmd->msg, 0};
  E_DialoguePush(cmd->ent->dialogue, l);

  entity_collection_t ents_heard =
      world_get_entities(cmd->game->world, cmd->ent->x, cmd->ent->y, 10);
  for (int i = 0; i < ents_heard.count; i++) {
    entity_t *eh = ents_heard.entities[i];
    if (eh == cmd->ent) {
      continue;
    }

    E_Hear(eh, cmd->game, l);
  }
}

void cb_ent_finished_thinking(ent_brain_think_request_t *r) {
  speech_push(&r->game->speech, r->response, r->entity);
  free(r);
}

void C_EntHear(void *data) {
  cmd_ent_hear_t *cmd = (cmd_ent_hear_t *)data;
  E_DialoguePush(cmd->ent->dialogue, cmd->line);

  ent_brain_think_request_t *r =
      (ent_brain_think_request_t *)malloc(sizeof(ent_brain_think_request_t));
  r->game = cmd->game;
  r->entity = cmd->ent;
  r->msg = cmd->line.line;
  ent_brain_think_and_answer(r, cb_ent_finished_thinking);
}
