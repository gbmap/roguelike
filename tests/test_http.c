
#define TB_IMPL
#include "../termbox2/termbox2.h"

#include "../game/http/http.h"
#include "../game/http/http_thread.h"

#include <assert.h>
#include <pthread.h>

http_client_t *c;

// ====================

void test_http_get() {
  printf("Testing GET... ");
  http_request_t r = http_create_request("GET", "https://www.pudim.com.br", 0);
  const char *result = http_send(c, r);
  assert(strlen(result) > 1);
  printf("OK\n");
}

// ====================

int g_http_req_done = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void on_http_request_done(http_request_t r, const char *res) {
  assert(strlen(res) > 1);

  pthread_mutex_lock(&mutex);
  g_http_req_done = g_http_req_done + 1;
  pthread_mutex_unlock(&mutex);
}

void test_http_thread() {
  printf("Testing HTTP THREAD... ");
  http_request_start_thread(c);
  assert(g_http_thread_is_running);

  http_request_t r = http_create_request("GET", "https://www.pudim.com.br", 0);
  const int n_requests = 15;
  for (int i = 0; i < n_requests; i++) {
    http_request_thread_push(r, on_http_request_done);
  }
  sleep(5);
  printf(" %i ", g_http_req_done);
  assert(g_http_req_done == n_requests);
  printf("OK\n");
}

// ====================

int main(int argc, char *argv[]) {
  c = http_client_init();
  test_http_get();
  test_http_thread();
  return 0;
}
