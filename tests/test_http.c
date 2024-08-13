
#define TB_IMPL
#include "../termbox2/termbox2.h"

#include "../game/u_network.h"

// ====================
//
//

int lock = 1;

void on_request_done(http_request_t r, const char *response) {
  printf("%s", response);
  lock = 0;
}

int main(int argc, char *argv[]) {
  G_NetworkInit();

  http_request_t r = G_HttpRequest("GET", "https://www.pudim.com.br", 0);
  G_NetworkSendHttp(r, on_request_done);

  while (lock) {
  }

  return 0;
}
