#include "click_count.h"
#include "unity.h"

static void test_fifth_and_tenth_click(void)
{
    int total = 0;
    int i;
    for (i = 1; i <= 4; i++) {
        TEST_ASSERT_EQUAL_INT(0, click_count_hit(&total, 5));
    }
    TEST_ASSERT_EQUAL_INT(1, click_count_hit(&total, 5));
    TEST_ASSERT_EQUAL_INT(5, total);
    for (i = 0; i < 4; i++) {
        TEST_ASSERT_EQUAL_INT(0, click_count_hit(&total, 5));
    }
    TEST_ASSERT_EQUAL_INT(1, click_count_hit(&total, 5));
    TEST_ASSERT_EQUAL_INT(10, total);
}

static void test_rejects_bad_arguments(void)
{
    int total = 3;
    TEST_ASSERT_EQUAL_INT(-1, click_count_hit(NULL, 5));
    TEST_ASSERT_EQUAL_INT(-1, click_count_hit(&total, 0));
    TEST_ASSERT_EQUAL_INT(-1, click_count_hit(&total, -2));
    TEST_ASSERT_EQUAL_INT(3, total);
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    UNITY_BEGIN();
    RUN_TEST(test_fifth_and_tenth_click);
    RUN_TEST(test_rejects_bad_arguments);
    return UNITY_END();
}
