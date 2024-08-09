#ifndef HTTP__H
#define HTTP__H

#include <curl/curl.h>

#define HTTP_MAX_HEADERS 10

typedef struct {
  const char *url;
  const char *body;
  const char *headers[HTTP_MAX_HEADERS];
} http_request_t;

http_request_t http_create_request(const char *url, const char *body);

typedef struct {
  CURL *curl;
} http_client_t;

http_client_t *http_client_init();
const char *http_get(http_client_t *h, http_request_t r);
const char *http_post(http_client_t *h, http_request_t r);

#endif
