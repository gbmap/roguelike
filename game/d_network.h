#ifndef __D_NETWORK__
#define __D_NETWORK__

#include <curl/curl.h>

//
//    HTTP
//
#define HTTP_MAX_HEADERS 10

typedef struct {
  const char *method;
  const char *url;
  const char *body;
  const char *headers[HTTP_MAX_HEADERS];
  void *data;
} http_request_t;

typedef struct {
  CURL *curl;
} http_client_t;

//
//    HTTP ASYNC TASK
//
typedef void (*http_request_callback)(http_request_t r, const char *response);

typedef struct {
  http_request_t req;
  http_request_callback callback;
} http_request_task_t;

#endif
