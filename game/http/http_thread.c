#include "http_thread.h"

#include <assert.h>
#include <pthread.h>
#include <unistd.h>

int g_http_thread_is_running = 0;
http_request_task_t g_tasks[HTTP_THREAD_MAX_TASKS];

void *http_request_thread(void *c) {
  while (g_http_thread_is_running) {
    for (int i = 0; i < HTTP_THREAD_MAX_TASKS; i++) {
      http_request_task_t *t = &g_tasks[i];
      if (t->callback != 0) {
        const char *res = http_send(c, t->req);
        t->callback(t->req, res);
        t->callback = 0; // null ptr callback is used to define invalid req
        break;
      }
    }
    usleep(500 * 1000);
  }
  pthread_exit(0);
}

void http_request_thread_push(http_request_t r, http_request_callback cb) {
  for (int i = 0; i < HTTP_THREAD_MAX_TASKS; i++) {
    http_request_task_t *t = &g_tasks[i];
    if (t->callback != 0) {
      continue;
    }

    t->req = r;
    t->callback = cb;
    break;
  }
}

void http_request_start_thread(http_client_t *c) {
  assert(!g_http_thread_is_running);

  pthread_t thread_id;
  pthread_create(&thread_id, 0, http_request_thread, (void *)c);
  g_http_thread_is_running = 1;
}
