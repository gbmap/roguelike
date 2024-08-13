#ifndef __G_NETWORK__
#define __G_NETWORK__

#include "d_network.h"
#include <pthread.h>

#define HTTP_THREAD_MAX_TASKS 128
extern http_request_task_t g_tasks[HTTP_THREAD_MAX_TASKS];
extern int g_http_thread_is_running;

extern http_client_t *httpclient;
extern pthread_t httpthread;

void G_NetworkInit();
void G_NetworkKill();
void G_NetworkSendHttp(http_request_t r, http_request_callback cb);
http_request_t G_HttpRequest(const char *method, const char *host,
                             const char *body);

#endif
