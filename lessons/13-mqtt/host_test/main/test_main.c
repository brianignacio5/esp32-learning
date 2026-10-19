#include <string.h>

#include "sensor_publish.h"
#include "unity.h"

static void test_topic(void)
{
    char buf[64];
    char tiny[21];
    memset(buf, 'x', sizeof buf);
    memset(tiny, 'x', sizeof tiny);
    TEST_ASSERT_EQUAL_INT(0, sensor_topic(buf, sizeof buf, "esp32"));
    TEST_ASSERT_EQUAL_STRING("sensors/esp32/reading", buf);
    TEST_ASSERT_EQUAL_INT(0, sensor_topic(buf, sizeof buf, "dev_1"));
    TEST_ASSERT_EQUAL_STRING("sensors/dev_1/reading", buf);
    TEST_ASSERT_EQUAL_INT(-1, sensor_topic(buf, sizeof buf, ""));
    TEST_ASSERT_EQUAL_INT(-1, sensor_topic(buf, sizeof buf, NULL));
    TEST_ASSERT_EQUAL_INT(-1, sensor_topic(buf, sizeof buf, "has space"));
    TEST_ASSERT_EQUAL_INT(-1, sensor_topic(buf, sizeof buf, "a/b"));
    TEST_ASSERT_EQUAL_INT(-1, sensor_topic(tiny, sizeof tiny, "esp32"));
    TEST_ASSERT_EQUAL_CHAR('x', tiny[0]);
}

static void test_payload(void)
{
    reading_t in = {.temp_c_x10 = 255, .humidity_pct = 40, .boot = 3};
    char buf[80];
    TEST_ASSERT_EQUAL_INT(0, sensor_payload(&in, buf, sizeof buf));
    TEST_ASSERT_EQUAL_STRING("{\"temp_c\":25.5,\"humidity\":40,\"boot\":3}", buf);
    in.temp_c_x10 = -5;
    TEST_ASSERT_EQUAL_INT(0, sensor_payload(&in, buf, sizeof buf));
    TEST_ASSERT_EQUAL_STRING("{\"temp_c\":-0.5,\"humidity\":40,\"boot\":3}", buf);
    TEST_ASSERT_EQUAL_INT(-1, sensor_payload(NULL, buf, sizeof buf));
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    UNITY_BEGIN();
    RUN_TEST(test_topic);
    RUN_TEST(test_payload);
    return UNITY_END();
}
