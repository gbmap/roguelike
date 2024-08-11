#ifndef HTTP_THREAD__H
#define HTTP_THREAD__H

/*
 * Thread that sends HTTP requests to endpoints
 * and callbacks with their results.
 */
#include "http.h"

typedef void (*http_request_callback)(http_request_t r, const char *response);

typedef struct {
  http_request_t req;
  http_request_callback callback;
} http_request_task_t;

#define HTTP_THREAD_MAX_TASKS 128
extern http_request_task_t g_tasks[HTTP_THREAD_MAX_TASKS];
extern int g_http_thread_is_running;

void *http_request_thread(void *c);
void http_request_thread_push(http_request_t r, http_request_callback cb);

void http_request_start_thread(http_client_t *c);

#endif
