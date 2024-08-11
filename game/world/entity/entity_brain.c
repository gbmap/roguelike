#include "entity_brain.h"

#include "../../../json/json.h"
#include "../../g_network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===================

char *OPENAI_API_KEY = 0;
const char *get_openai_api_key() {
  if (OPENAI_API_KEY) {
    return OPENAI_API_KEY;
  }

  char *api_key = getenv("OPENAI_API_KEY");
  if (api_key == 0) {
    printf("\nNo API key configured. OPENAI_API_KEY=your key\n");
    exit(-1);
  }

  int hbuflen = strlen(api_key) + 1 + strlen("Authorization: Bearer ");
  OPENAI_API_KEY = (char *)malloc(hbuflen);
  snprintf(OPENAI_API_KEY, hbuflen, "Authorization: Bearer %s", api_key);
  return OPENAI_API_KEY;
}

const char *parse_openai_response(const char *msg) {
  result(json_element) element_result = json_parse(msg);

  if (result_is_err(json_element)(&element_result)) {
    typed(json_error) error = result_unwrap_err(json_element)(&element_result);
    return "ERROR";
  }

  typed(json_element) element = result_unwrap(json_element)(&element_result);

  result(json_element) choices_element_result =
      json_object_find(element.value.as_object, "choices");

  if (result_is_err(json_element)(&choices_element_result)) {
    typed(json_error) error =
        result_unwrap_err(json_element)(&choices_element_result);
    return "ERROR";
  }
  typed(json_element) choices_element =
      result_unwrap(json_element)(&choices_element_result);

  typed(json_array) *arr = choices_element.value.as_array;
  typed(json_element) choice_element = arr->elements[0];

  result(json_element) message_element_result =
      json_object_find(choice_element.value.as_object, "message");
  typed(json_element) message_element =
      result_unwrap(json_element)(&message_element_result);

  result(json_element) content_element_result =
      json_object_find(message_element.value.as_object, "content");
  typed(json_element) content_element =
      result_unwrap(json_element)(&content_element_result);

  return content_element.value.as_string;
}

#define PAYLOAD_BUFFERS_SIZE 32
#define PAYLOAD_MAX_SIZE 4096
char *PAYLOAD_BUFFERS[PAYLOAD_BUFFERS_SIZE];
int PAYLOAD_CURSOR = -1;

const char *openai_payload(const char *msg) {
  if (PAYLOAD_CURSOR == -1) {
    PAYLOAD_CURSOR = 0;
    for (int i = 0; i < PAYLOAD_BUFFERS_SIZE; i++) {
      PAYLOAD_BUFFERS[i] = (char *)malloc(sizeof(char) * PAYLOAD_MAX_SIZE);
      memset(PAYLOAD_BUFFERS[i], '\0', PAYLOAD_MAX_SIZE);
    }
  }

  const char *PAYLOAD_TEMPLATE =
      "{ \"model\": \"gpt-4o-mini\", \"messages\": [{\"role\": \"user\", "
      "\"content\": \"%s\"}], "
      "\"temperature\": 0.9 }";

  int sz = strlen(PAYLOAD_TEMPLATE) + strlen(msg);
  char *buf = PAYLOAD_BUFFERS[PAYLOAD_CURSOR];
  snprintf(buf, sz, PAYLOAD_TEMPLATE, msg);
  PAYLOAD_CURSOR = (PAYLOAD_CURSOR + 1) % PAYLOAD_BUFFERS_SIZE;
  return buf;
}

// =================

typedef struct {
  ent_brain_think_request_t *r;
  ent_brain_think_callback cb;
} _ent_brain_think_t;

void cb_ent_brain_thonk(http_request_t r, const char *response) {
  _ent_brain_think_t *t = ((_ent_brain_think_t *)r.data);
  t->r->response = response;
  t->cb(t->r);
  free(t);
}

void ent_brain_think_and_answer(ent_brain_think_request_t *req,
                                ent_brain_think_callback cb) {
  http_request_t r;
  r.method = "POST";
  r.url = "https://api.openai.com/v1/chat/completions";
  r.body = openai_payload(req->msg);
  r.headers[0] = "Content-Type: application/json";
  r.headers[1] = get_openai_api_key();

  _ent_brain_think_t *t =
      (_ent_brain_think_t *)malloc(sizeof(_ent_brain_think_t));
  t->r = req;
  t->cb = cb;
  r.data = t;

  const char *_DEBUG_RESP =
      "{"
      "\"id\": \"chatcmpl-9u3m3jcfVbW0w1PjSqfsYd89dq5a7\","
      "\"object\": \"chat.completion\","
      "\"created\": 1723147903,"
      "\"model\": \"gpt-4o-mini-2024-07-18\","
      "\"choices\": ["
      "{"
      "\"index\": 0,"
      "\"message\": {"
      "\"role\": \"assistant\","
      "\"content\": \"This is a test! How can I assist you further?\","
      "\"refusal\": null"
      "},"
      "\"logprobs\": null,"
      "\"finish_reason\": \"stop\""
      "}"
      "],"
      "\"usage\": {"
      "\"prompt_tokens\": 13,"
      "\"completion_tokens\": 12,"
      "\"total_tokens\": 25"
      "},"
      "\"system_fingerprint\": \"fp_48196bc67a\""
      "}";

  cb_ent_brain_thonk(r, parse_openai_response(_DEBUG_RESP));
  return;

  // TODO: generate openai JSON with msg (check sandbox)
  // r.body = req->msg;
  // and alocate a _ent_brain_think_t* and set data
  // r.data = ...;

  G_NetworkSendHttp(r, cb_ent_brain_thonk);
}
