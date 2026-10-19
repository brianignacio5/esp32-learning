#include "http_line.h"

int build_http_get(char *buf, size_t len, const char *host, const char *path)
{
    /* TODO: write the request from http_line.h. Leave buf unchanged on failure. */
    (void)buf;
    (void)len;
    (void)host;
    (void)path;
    return -1;
}

int parse_status_code(const char *response, int *code)
{
    /* TODO: find the three-digit status code. */
    (void)response;
    (void)code;
    return -1;
}
