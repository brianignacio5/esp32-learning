#pragma once

#include <stddef.h>

/* Send request to host port 80 and copy the status line into line.
   The trailing CR LF is not included. Returns 0 when a line was read. */
int http_exchange(const char *host, const char *request, char *line, size_t line_len);
