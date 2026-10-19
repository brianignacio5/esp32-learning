#include <string.h>

#include "http_line.h"
#include "unity.h"

static void test_builds_example_request(void)
{
    char buf[128];
    const char *expect = "GET / HTTP/1.0\r\nHost: example.com\r\nConnection: close\r\n\r\n";
    memset(buf, 'x', sizeof buf);
    TEST_ASSERT_EQUAL_INT(0, build_http_get(buf, sizeof buf, "example.com", "/"));
    TEST_ASSERT_EQUAL_STRING(expect, buf);
}

static void test_build_rejects_bad_input(void)
{
    char buf[16];
    char big[128];
    memset(buf, 'x', sizeof buf);
    buf[sizeof buf - 1] = '\0';
    TEST_ASSERT_EQUAL_INT(-1, build_http_get(NULL, 16, "example.com", "/"));
    TEST_ASSERT_EQUAL_INT(-1, build_http_get(buf, sizeof buf, "example.com", "/"));
    TEST_ASSERT_EQUAL_CHAR('x', buf[0]);
    memset(big, 'x', sizeof big);
    TEST_ASSERT_EQUAL_INT(-1, build_http_get(big, sizeof big, "example.com", "status"));
    TEST_ASSERT_EQUAL_CHAR('x', big[0]);
    TEST_ASSERT_EQUAL_INT(-1, build_http_get(big, sizeof big, "", "/"));
}

static void test_parses_status_codes(void)
{
    int code = 0;
    TEST_ASSERT_EQUAL_INT(0, parse_status_code("HTTP/1.1 200 OK\r\n", &code));
    TEST_ASSERT_EQUAL_INT(200, code);
    TEST_ASSERT_EQUAL_INT(0, parse_status_code("HTTP/1.0 404 Not Found", &code));
    TEST_ASSERT_EQUAL_INT(404, code);
    TEST_ASSERT_EQUAL_INT(0, parse_status_code("HTTP/1.1 201 Created", &code));
    TEST_ASSERT_EQUAL_INT(201, code);
}

static void test_parse_rejects_junk(void)
{
    int code = 9;
    TEST_ASSERT_EQUAL_INT(-1, parse_status_code("not http", &code));
    TEST_ASSERT_EQUAL_INT(9, code);
    TEST_ASSERT_EQUAL_INT(-1, parse_status_code("HTTP/1.1 OK", &code));
    TEST_ASSERT_EQUAL_INT(-1, parse_status_code(NULL, &code));
    TEST_ASSERT_EQUAL_INT(-1, parse_status_code("HTTP/1.1 200 OK", NULL));
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    UNITY_BEGIN();
    RUN_TEST(test_builds_example_request);
    RUN_TEST(test_build_rejects_bad_input);
    RUN_TEST(test_parses_status_codes);
    RUN_TEST(test_parse_rejects_junk);
    return UNITY_END();
}
