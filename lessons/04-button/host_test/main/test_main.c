#include "debounce.h"
#include "unity.h"

static void test_accepts_after_three_samples(void)
{
    debounce_t db;
    debounce_init(&db, 1);

    TEST_ASSERT_EQUAL_INT(0, debounce_update(&db, 0, 3));
    TEST_ASSERT_EQUAL_INT(1, db.stable);
    TEST_ASSERT_EQUAL_INT(0, debounce_update(&db, 0, 3));
    TEST_ASSERT_EQUAL_INT(1, debounce_update(&db, 0, 3));
    TEST_ASSERT_EQUAL_INT(0, db.stable);
    TEST_ASSERT_EQUAL_INT(0, debounce_update(&db, 0, 3));
}

static void test_noise_restarts_the_count(void)
{
    debounce_t db;
    debounce_init(&db, 1);

    TEST_ASSERT_EQUAL_INT(0, debounce_update(&db, 0, 3));
    TEST_ASSERT_EQUAL_INT(0, debounce_update(&db, 0, 3));
    TEST_ASSERT_EQUAL_INT(0, debounce_update(&db, 1, 3));
    TEST_ASSERT_EQUAL_INT(1, db.stable);
    TEST_ASSERT_EQUAL_INT(0, debounce_update(&db, 0, 3));
    TEST_ASSERT_EQUAL_INT(0, debounce_update(&db, 0, 3));
    TEST_ASSERT_EQUAL_INT(1, debounce_update(&db, 0, 3));
    TEST_ASSERT_EQUAL_INT(0, db.stable);
}

static void test_rising_edge_and_need_of_one(void)
{
    debounce_t db;
    debounce_init(&db, 0);
    TEST_ASSERT_EQUAL_INT(1, debounce_update(&db, 1, 1));
    TEST_ASSERT_EQUAL_INT(1, db.stable);
    TEST_ASSERT_EQUAL_INT(0, debounce_update(&db, 1, 1));
}

static void test_ignores_bad_arguments(void)
{
    debounce_t db;
    debounce_init(&db, 1);
    TEST_ASSERT_EQUAL_INT(0, debounce_update(NULL, 0, 3));
    TEST_ASSERT_EQUAL_INT(0, debounce_update(&db, 2, 1));
    TEST_ASSERT_EQUAL_INT(1, db.stable);
    TEST_ASSERT_EQUAL_INT(0, db.count);
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    UNITY_BEGIN();
    RUN_TEST(test_accepts_after_three_samples);
    RUN_TEST(test_noise_restarts_the_count);
    RUN_TEST(test_rising_edge_and_need_of_one);
    RUN_TEST(test_ignores_bad_arguments);
    return UNITY_END();
}
