# Lesson 11 — An HTTP GET and its status line

About one hour. Building the request and reading the status code are plain string functions. The socket helper that sends them is already written.

## What you will learn

- The shape of a minimal HTTP/1.0 request
- How to find the three-digit status code on a response status line
- Where that function sits next to a connected TCP socket

## The task

Implement both functions in `logic/http_line.c`. The header is the contract.

`build_http_get` writes:

```text
GET / HTTP/1.0
Host: example.com
Connection: close


```

The path must start with `/`. Return -1 when the arguments are unusable or the buffer is too small. Do not write a partial request in that case.

`parse_status_code` reads a line such as `HTTP/1.1 200 OK` and stores `200`. It should accept `HTTP/1.0` and `HTTP/1.1`. Return -1 when the line has no three-digit code.

`firmware/main/app_main.c` joins Wi-Fi, builds a GET for `http://example.com/`, reads the status line, and logs `status=<code>`. You do not have to write the socket code. Read `http_exchange.c` so you know what your request string must contain.

## Acceptance

- The example.com request above matches that text exactly, including the blank line
- `HTTP/1.1 200 OK`, `HTTP/1.0 404 Not Found`, and `HTTP/1.1 201 Created` parse to 200, 404, and 201
- A line that is not an HTTP status returns -1
- `./scripts/check-lesson.sh 11` passes

## Read

- [BSD sockets](https://docs.espressif.com/projects/esp-idf/en/v6.0.3/esp32/api-reference/network/esp_netif.html) and the provided `http_exchange.c`
- Example to read after you finish: [protocols/http_request](https://github.com/espressif/esp-idf/tree/v6.0.3/examples/protocols/http_request)

## Build and simulate

```bash
./scripts/check-lesson.sh 11
```

The firmware project is `lessons/11-http/firmware`. A live GET of `example.com` is a smoke test. Public HTTP from the simulator can fail even when your parser is correct, so it is not the gate.

```bash
wokwi-cli . --scenario scenario.optional.yaml --timeout 120000
```

Run that from the firmware directory after a build, with `WOKWI_CLI_TOKEN` set.

## Check

The host test is the pass/fail gate.

## Solution

`logic/solution/http_line.c`.

## Hints

- `snprintf(NULL, 0, ...)` returns the length you need. If `need + 1` is greater than `len`, return -1 before writing.
- Find `HTTP/1.`, then the next space, then three digits. Do not assume the reason phrase.
