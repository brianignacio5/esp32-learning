#include "dht_decode.h"
#include "unity.h"

static void test_room_reading(void)
{
    const uint8_t frame[5] = {0x01, 0x90, 0x00, 0xFF, 0x90};
    dht_reading_t out = {0};
    TEST_ASSERT_EQUAL_INT(0, dht_decode(frame, &out));
    TEST_ASSERT_EQUAL_INT(1, out.ok);
    TEST_ASSERT_EQUAL_INT(400, out.humidity_x10);
    TEST_ASSERT_EQUAL_INT(255, out.temp_c_x10);
}

static void test_negative_temperature(void)
{
    const uint8_t frame[5] = {0x01, 0x90, 0x80, 0x37, 0x48};
    dht_reading_t out = {0};
    TEST_ASSERT_EQUAL_INT(0, dht_decode(frame, &out));
    TEST_ASSERT_EQUAL_INT(-55, out.temp_c_x10);
    TEST_ASSERT_EQUAL_INT(400, out.humidity_x10);
}

static void test_bad_checksum_leaves_output(void)
{
    const uint8_t frame[5] = {0x01, 0x90, 0x00, 0xFF, 0x00};
    dht_reading_t out = {.ok = 7, .temp_c_x10 = 1, .humidity_x10 = 2};
    TEST_ASSERT_EQUAL_INT(-1, dht_decode(frame, &out));
    TEST_ASSERT_EQUAL_INT(7, out.ok);
    TEST_ASSERT_EQUAL_INT(1, out.temp_c_x10);
    TEST_ASSERT_EQUAL_INT(2, out.humidity_x10);
    TEST_ASSERT_EQUAL_INT(-1, dht_decode(NULL, &out));
    TEST_ASSERT_EQUAL_INT(-1, dht_decode(frame, NULL));
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    UNITY_BEGIN();
    RUN_TEST(test_room_reading);
    RUN_TEST(test_negative_temperature);
    RUN_TEST(test_bad_checksum_leaves_output);
    return UNITY_END();
}
