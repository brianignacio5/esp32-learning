#include "http_line.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

int build_http_get(char *buf, size_t len, const char *host, const char *path)
{
    int need;

    if (buf == NULL || host == NULL || path == NULL || host[0] == '\0' || path[0] != '/') {
        return -1;
    }
    need = snprintf(NULL, 0, "GET %s HTTP/1.0\r\nHost: %s\r\nConnection: close\r\n\r\n", path, host);
    if (need < 0 || (size_t)need + 1 > len) {
        return -1;
    }
    snprintf(buf, len, "GET %s HTTP/1.0\r\nHost: %s\r\nConnection: close\r\n\r\n", path, host);
    return 0;
}

int parse_status_code(const char *response, int *code)
{
    const char *mark;
    const char *digits;

    if (response == NULL || code == NULL) {
        return -1;
    }
    mark = strstr(response, "HTTP/1.");
    if (mark == NULL) {
        return -1;
    }
    digits = strchr(mark, ' ');
    if (digits == NULL) {
        return -1;
    }
    digits++;
    if (!isdigit((unsigned char)digits[0]) || !isdigit((unsigned char)digits[1]) ||
        !isdigit((unsigned char)digits[2])) {
        return -1;
    }
    *code = (digits[0] - '0') * 100 + (digits[1] - '0') * 10 + (digits[2] - '0');
    return 0;
}
