#include "g_network.h"

#include <assert.h>
#include <curl/curl.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

http_request_task_t g_tasks[HTTP_THREAD_MAX_TASKS];
int g_http_thread_is_running = 0;
http_client_t *httpclient;
pthread_t httpthread;

http_request_t http_create_request(const char *method, const char *url,
                                   const char *body) {
  http_request_t r = {method, url, body};
  for (int i = 0; i < HTTP_MAX_HEADERS; i++) {
    r.headers[i] = "\0";
  }
  r.data = 0;
  return r;
}

http_request_t G_HttpRequest(const char *method, const char *host,
                             const char *body) {
  return http_create_request(method, host, body);
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
  while (req->buflen < req->len + realsize + 1) {
    req->buffer = realloc(req->buffer, req->buflen + CHUNK_SIZE);
    req->buflen += CHUNK_SIZE;
  }
  memcpy(&req->buffer[req->len], ptr, realsize);
  req->len += realsize;
  req->buffer[req->len] = 0;
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

const char *_http_send(http_client_t *h, http_request_t r) {
  return _http_request(h, r.method, r);
}

// =====================
//    THREAD STUFF

void *http_request_thread(void *c) {
  while (g_http_thread_is_running) {
    for (int i = 0; i < HTTP_THREAD_MAX_TASKS; i++) {
      http_request_task_t *t = &g_tasks[i];
      if (t->callback != 0) {
        const char *res = _http_send(c, t->req);
        t->callback(t->req, res);
        t->callback = 0; // null ptr callback is used to define invalid req
        break;
      }
    }
    usleep(500 * 1000);
  }
  pthread_exit(0);
}

void http_request_start_thread(http_client_t *c) {
  assert(!g_http_thread_is_running);

  pthread_create(&httpthread, 0, http_request_thread, (void *)c);
  g_http_thread_is_running = 1;
}

void G_NetworkInit() {
  httpclient = http_client_init();
  http_request_start_thread(httpclient);
}

void G_NetworkKill() {
  free(httpclient);
  httpclient = 0;
  g_http_thread_is_running = 0;
}

void G_NetworkSendHttp(http_request_t r, http_request_callback cb) {
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
