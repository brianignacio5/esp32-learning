#pragma once

#include <stddef.h>

/* Write "GET <path> HTTP/1.0\r\nHost: <host>\r\nConnection: close\r\n\r\n".
   path must start with '/'. host must be non-empty.
   Returns 0, or -1 when an argument is unusable or the text does not fit.
   On failure the buffer is left unchanged. */
int build_http_get(char *buf, size_t len, const char *host, const char *path);

/* Store the three-digit code from a status line such as "HTTP/1.1 200 OK".
   Accepts HTTP/1.0 and HTTP/1.1. Returns 0, or -1 when the code is missing. */
int parse_status_code(const char *response, int *code);
