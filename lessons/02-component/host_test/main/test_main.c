#include <string.h>

#include "format_reading.h"
#include "unity.h"

static void test_typical_reading(void)
{
    char buf[32];
    int n = format_reading(buf, sizeof buf, 235, 40);
    TEST_ASSERT_EQUAL_INT(9, n);
    TEST_ASSERT_EQUAL_STRING("23.5C 40%", buf);
}

static void test_negative_and_zero(void)
{
    char buf[32];

    TEST_ASSERT_EQUAL_INT(0, format_reading(buf, sizeof buf, -55, 40) < 0 ? -1 : 0);
    TEST_ASSERT_EQUAL_STRING("-5.5C 40%", buf);
    format_reading(buf, sizeof buf, -5, 0);
    TEST_ASSERT_EQUAL_STRING("-0.5C 0%", buf);
    format_reading(buf, sizeof buf, 0, 100);
    TEST_ASSERT_EQUAL_STRING("0.0C 100%", buf);
    format_reading(buf, sizeof buf, 5, 7);
    TEST_ASSERT_EQUAL_STRING("0.5C 7%", buf);
}

static void test_rejects_bad_buffer(void)
{
    char buf[8];
    TEST_ASSERT_EQUAL_INT(-1, format_reading(NULL, 8, 235, 40));
    TEST_ASSERT_EQUAL_INT(-1, format_reading(buf, 0, 235, 40));
}

static void test_truncates_like_snprintf(void)
{
    char buf[4];
    int n = format_reading(buf, sizeof buf, 235, 40);
    TEST_ASSERT_EQUAL_INT(9, n);
    TEST_ASSERT_EQUAL_CHAR('\0', buf[3]);
    TEST_ASSERT_EQUAL_STRING("23.", buf);
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    UNITY_BEGIN();
    RUN_TEST(test_typical_reading);
    RUN_TEST(test_negative_and_zero);
    RUN_TEST(test_rejects_bad_buffer);
    RUN_TEST(test_truncates_like_snprintf);
    return UNITY_END();
}
