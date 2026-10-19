#include "raw_to_percent.h"
#include "unity.h"

static void test_clamps_ends(void)
{
    TEST_ASSERT_EQUAL_INT(0, raw_to_percent(0));
    TEST_ASSERT_EQUAL_INT(0, raw_to_percent(-10));
    TEST_ASSERT_EQUAL_INT(100, raw_to_percent(4095));
    TEST_ASSERT_EQUAL_INT(100, raw_to_percent(5000));
}

static void test_rounds_to_nearest(void)
{
    TEST_ASSERT_EQUAL_INT(50, raw_to_percent(2048));
    TEST_ASSERT_EQUAL_INT(0, raw_to_percent(20));
    TEST_ASSERT_EQUAL_INT(1, raw_to_percent(21));
    TEST_ASSERT_EQUAL_INT(100, raw_to_percent(4094));
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    UNITY_BEGIN();
    RUN_TEST(test_clamps_ends);
    RUN_TEST(test_rounds_to_nearest);
    return UNITY_END();
}
