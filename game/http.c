
#include "http.h"
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

http_request_t http_create_request(const char *url, const char *body) {
  http_request_t r;
  r.url = url;
  r.body = body;
  for (int i = 0; i < HTTP_MAX_HEADERS; i++) {
    r.headers[i] = "\0";
  }
  return r;
}

// ==============
//
//

#define CHUNK_SIZE 2048

typedef struct {
  char *buffer;
  size_t len;
  size_t buflen;
} http_response_t;

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
  size_t realsize = size * nmemb;
  http_response_t *req = (http_response_t *)userdata;

  printf("receive chunk of %zu bytes\n", realsize);

  while (req->buflen < req->len + realsize + 1) {
    req->buffer = realloc(req->buffer, req->buflen + CHUNK_SIZE);
    req->buflen += CHUNK_SIZE;
  }
  memcpy(&req->buffer[req->len], ptr, realsize);
  req->len += realsize;
  req->buffer[req->len] = 0;

  printf("%s", req->buffer);

  return realsize;
}

http_client_t *http_client_init() {
  http_client_t *c = (http_client_t *)malloc(sizeof(http_client_t));
  c->curl = curl_easy_init();
  return c;
}

const char *_http_request(http_client_t *h, const char *method,
                          http_request_t r) {
  CURL *curl = h->curl;
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method);
  curl_easy_setopt(curl, CURLOPT_URL, r.url);
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");

  struct curl_slist *chunk = 0;
  int n_headers = 0;
  for (int i = 0; i < HTTP_MAX_HEADERS; i++) {
    if (strncmp(r.headers[i], "\0", 1) == 0) {
      chunk = curl_slist_append(chunk, r.headers[i]);
      n_headers++;
    }
  }

  if (n_headers > 0) {
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
  }

  if (strcmp(method, "POST") == 0) {
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, r.body);
  }

  http_response_t response = {0, 0, 0};
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

  curl_easy_perform(curl);

  return response.buffer;
}

const char *http_get(http_client_t *h, http_request_t r) {
  return _http_request(h, "GET", r);
}

const char *http_post(http_client_t *h, http_request_t r) {
  return _http_request(h, "POST", r);
}
