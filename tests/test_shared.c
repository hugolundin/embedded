#include "unity.h"

void setUp(void)
{
  
}

void tearDown(void)
{
}

void test_hej(void)
{
  TEST_ASSERT_EQUAL(2, 2);
}

int main(int argc, char const *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_hej);
    return UNITY_END();
}
