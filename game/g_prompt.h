#ifndef __G_PROMPT__
#define __G_PROMPT__

#include "d_world.h"

const char *E_PromptPreamble();
const char *E_PromptDialogue(line_t *line);
const char *E_PromptOpinion(opinion_collection_t *c);

const char *E_PromptActionSay(entity_t *e);

#endif
