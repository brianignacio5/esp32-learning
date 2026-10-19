#include "http_exchange.h"

#include <string.h>

#include "lwip/netdb.h"
#include "lwip/sockets.h"

int http_exchange(const char *host, const char *request, char *line, size_t line_len)
{
    struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
    };
    struct addrinfo *res = NULL;
    struct timeval timeout = {.tv_sec = 8, .tv_usec = 0};
    int sock = -1;
    size_t used = 0;
    int rc = -1;

    if (host == NULL || request == NULL || line == NULL || line_len == 0) {
        return -1;
    }
    if (getaddrinfo(host, "80", &hints, &res) != 0 || res == NULL) {
        return -1;
    }
    sock = socket(res->ai_family, res->ai_socktype, 0);
    if (sock < 0) {
        freeaddrinfo(res);
        return -1;
    }
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout);
    if (connect(sock, res->ai_addr, res->ai_addrlen) != 0) {
        goto done;
    }
    if (send(sock, request, strlen(request), 0) < 0) {
        goto done;
    }
    while (used + 1 < line_len) {
        char ch = 0;
        int n = recv(sock, &ch, 1, 0);
        if (n <= 0 || ch == '\n') {
            break;
        }
        if (ch != '\r') {
            line[used++] = ch;
        }
    }
    line[used] = '\0';
    rc = used > 0 ? 0 : -1;

done:
    if (sock >= 0) {
        closesocket(sock);
    }
    freeaddrinfo(res);
    return rc;
}
