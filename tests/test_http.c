
#define TB_IMPL
#include "../termbox2/termbox2.h"

#include "../game/http.h"

#include <assert.h>

const char *test_http_get() {
  http_client_t *h = http_client_init();
  http_request_t r = http_create_request("https://www.pudim.com.br", 0);
  const char *result = http_get(h, r);
  return result;
}

const char *test_http_post() { return ""; }

int main(int argc, char *argv[]) {
  printf("Testing GET...\n");
  const char *r = test_http_get();
  assert(strlen(r) > 1);
  return 0;
}
