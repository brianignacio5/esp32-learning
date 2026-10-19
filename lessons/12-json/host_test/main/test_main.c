#include <string.h>

#include "cJSON.h"
#include "reading_json.h"
#include "unity.h"

static void test_exact_object(void)
{
    reading_t in = {.temp_c_x10 = 255, .humidity_pct = 40, .boot = 3};
    char buf[80];
    cJSON *root;
    cJSON *temp;

    memset(buf, 'x', sizeof buf);
    TEST_ASSERT_EQUAL_INT(0, reading_to_json(&in, buf, sizeof buf));
    TEST_ASSERT_EQUAL_STRING("{\"temp_c\":25.5,\"humidity\":40,\"boot\":3}", buf);

    root = cJSON_Parse(buf);
    TEST_ASSERT_NOT_NULL(root);
    temp = cJSON_GetObjectItem(root, "temp_c");
    TEST_ASSERT_NOT_NULL(temp);
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 25.5, temp->valuedouble);
    TEST_ASSERT_EQUAL_INT(40, cJSON_GetObjectItem(root, "humidity")->valueint);
    TEST_ASSERT_EQUAL_INT(3, cJSON_GetObjectItem(root, "boot")->valueint);
    cJSON_Delete(root);
}

static void test_negative_temperature(void)
{
    reading_t in = {.temp_c_x10 = -55, .humidity_pct = 40, .boot = 3};
    char buf[80];
    TEST_ASSERT_EQUAL_INT(0, reading_to_json(&in, buf, sizeof buf));
    TEST_ASSERT_EQUAL_STRING("{\"temp_c\":-5.5,\"humidity\":40,\"boot\":3}", buf);
}

static void test_rejects_short_buffer(void)
{
    reading_t in = {.temp_c_x10 = 255, .humidity_pct = 40, .boot = 3};
    char buf[8];
    memset(buf, 'x', sizeof buf);
    TEST_ASSERT_EQUAL_INT(-1, reading_to_json(NULL, buf, sizeof buf));
    TEST_ASSERT_EQUAL_INT(-1, reading_to_json(&in, buf, sizeof buf));
    TEST_ASSERT_EQUAL_CHAR('x', buf[0]);
    TEST_ASSERT_EQUAL_INT(-1, reading_to_json(&in, NULL, 8));
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    UNITY_BEGIN();
    RUN_TEST(test_exact_object);
    RUN_TEST(test_negative_temperature);
    RUN_TEST(test_rejects_short_buffer);
    return UNITY_END();
}
