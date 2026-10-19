#include <string.h>

#include "unity.h"
#include "weather.h"

static void test_should_publish(void)
{
    sample_t now = {.temp_c_x10 = 250, .humidity_pct = 40};
    sample_t last = now;
    sample_t warmer = {.temp_c_x10 = 255, .humidity_pct = 40};
    sample_t slightly = {.temp_c_x10 = 254, .humidity_pct = 40};
    sample_t colder = {.temp_c_x10 = 240, .humidity_pct = 40};
    sample_t humid = {.temp_c_x10 = 250, .humidity_pct = 42};

    TEST_ASSERT_EQUAL_INT(0, should_publish(NULL, NULL, 1, 5, 2));
    TEST_ASSERT_EQUAL_INT(0, should_publish(NULL, &now, 0, -1, 2));
    TEST_ASSERT_EQUAL_INT(1, should_publish(NULL, &now, 0, 5, 2));
    TEST_ASSERT_EQUAL_INT(0, should_publish(&last, &now, 0, 5, 2));
    TEST_ASSERT_EQUAL_INT(1, should_publish(&last, &now, 1, 5, 2));
    TEST_ASSERT_EQUAL_INT(1, should_publish(&last, &warmer, 0, 5, 2));
    TEST_ASSERT_EQUAL_INT(0, should_publish(&last, &slightly, 0, 5, 2));
    TEST_ASSERT_EQUAL_INT(1, should_publish(&last, &colder, 0, 5, 2));
    TEST_ASSERT_EQUAL_INT(1, should_publish(&last, &humid, 0, 5, 2));
}

static void test_payload(void)
{
    char buf[80];
    char small[8];
    memset(small, 'x', sizeof small);
    TEST_ASSERT_EQUAL_INT(0, reading_to_json(255, 40, 1, buf, sizeof buf));
    TEST_ASSERT_EQUAL_STRING("{\"temp_c\":25.5,\"humidity\":40,\"boot\":1}", buf);
    TEST_ASSERT_EQUAL_INT(-1, reading_to_json(255, 40, 1, small, sizeof small));
    TEST_ASSERT_EQUAL_CHAR('x', small[0]);
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    UNITY_BEGIN();
    RUN_TEST(test_should_publish);
    RUN_TEST(test_payload);
    return UNITY_END();
}
