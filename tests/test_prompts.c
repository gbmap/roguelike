
#define TB_IMPL
#include "../termbox2/termbox2.h"

#include "../game/g_entity.h"
#include "../game/g_prompt.h"

opinion_collection_t gen_opinions() {
  opinion_collection_t c = E_NewOpinionCollection();

  opinion_t o1 = {"Carnivorism", 0.856};
  opinion_t o2 = {"Arguing", 0.7};
  opinion_t o3 = {"Discussions", -0.34};
  c.opinions[0] = o1;
  c.opinions[1] = o2;
  c.opinions[2] = o3;
  return c;
}

void test_prompt_opinion() {
  printf("\n=================\n");

  opinion_collection_t c = gen_opinions();
  printf("%s", E_PromptOpinion(&c));

  printf("\n=================\n");
}

line_t *gen_dialogue() {
  line_t l0 = {"Rudolph McWhopper", "Finna get me some whoppers!", 0};
  line_t *dialogue = E_DialoguePush(0, l0);

  line_t l1 = {
      "Hamburglar",
      "Whoppers are meat and meat is murder. You should consider veganism.", 0};
  dialogue = E_DialoguePush(dialogue, l1);

  // line_t l2 = {"Rudolph McWhopper", "What are you gonna do, shitty mime?",
  // 0}; dialogue = E_DialoguePush(dialogue, l2);
  return dialogue;
}

void test_prompt_dialogue() {
  line_t *dialogue = gen_dialogue();

  printf("\n=================\n");
  const char *prompt = E_PromptDialogue(dialogue);
  printf("%s", prompt);
  printf("\n=================\n");
}

void test_prompt_action_say() {
  opinion_collection_t o = gen_opinions();
  line_t *dialogue = gen_dialogue();
  entity_t e = {0, 0, 0, 0, "X", "a", dialogue, o};

  printf("\n=================\n");
  const char *prompt = E_PromptActionSay(&e);
  printf("%s", prompt);
  printf("\n=================\n");
}

int main(int argc, char *argv[]) {
  test_prompt_opinion();
  test_prompt_dialogue();
  test_prompt_action_say();
}
