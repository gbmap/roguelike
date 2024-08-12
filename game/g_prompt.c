#include "g_prompt.h"
#include "d_game.h"
#include "d_world.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *prmpt_preamble;
const char *prmpt_opinion;

const char *read_file(const char *file) {
  FILE *f = fopen(file, "r");
  char *contents = (char *)malloc(sizeof(char) * 4096);
  fgets(contents, 4096, f);
  return contents;
}

const char *E_PromptPreamble() {
  if (!prmpt_preamble) {
    prmpt_preamble = read_file("data/prompts/preamble.txt");
  }
  return prmpt_preamble;
}

const char *E_PromptOpinion(opinion_collection_t *c) {
  if (!prmpt_opinion) {
    prmpt_opinion = read_file("data/prompts/opinions.txt");
  }

  int opinions_str_len =
      strlen(prmpt_opinion) +
      (ENT_MAX_OPINION_NAME_SZ + ENT_MAX_OPINION_DEC_SZ) * ENT_MAX_OPINIONS;

  char *str_opinions = (char *)malloc(opinions_str_len);
  memset(str_opinions, '\0', opinions_str_len * sizeof(char));

  strcat(str_opinions, prmpt_opinion);
  char *ptr_opinion = str_opinions + strlen(str_opinions);

  for (int i = 0; i < ENT_MAX_OPINIONS; i++) {
    opinion_t *o = &c->opinions[i];
    if (strcmp(c->opinions[i].name, "\0") == 0) {
      continue;
    }
    sprintf(ptr_opinion, "%s: %f\n", o->name, o->value);
    ptr_opinion = str_opinions + strlen(str_opinions);
  }

  return str_opinions;
}

const char *E_PromptDialogue(line_t *line) {
  const int max_dialogue_size =
      ENT_MAX_DIALOGUE_LEN * (ENT_MAX_NAME_SZ + SPEECH_BOX_MSG_SIZE + 3);
  char *dialogue = (char *)malloc(max_dialogue_size);
  dialogue[0] = '\0';

  char *ptr = dialogue;
  do {
    sprintf(ptr, "%s: %s\n", line->name, line->line);
    ptr += strlen(ptr);
    line = line->next;
  } while (line);

  return dialogue;
}

const char *E_PromptActionSay(entity_t *e) {
  const char *preamble = E_PromptPreamble();
  const char *opinions = E_PromptOpinion(&e->opinions);
  const char *dialogue = E_PromptDialogue(e->dialogue);
  const char *action_answer = read_file("data/prompts/action_answer.txt");

  char *prompt =
      (char *)malloc(sizeof(char) * (strlen(preamble) + strlen(opinions)) +
                     strlen(dialogue) + strlen(action_answer));

  strcat(prompt, preamble);
  strcat(prompt, "\n");
  strcat(prompt, opinions);
  strcat(prompt, "\n");
  strcat(prompt, "Dialogue heard:\n");
  strcat(prompt, dialogue);
  strcat(prompt, "\n");
  strcat(prompt, action_answer);
  return prompt;
}
