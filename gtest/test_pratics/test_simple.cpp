#include <gtest/gtest.h>

int add(int a, int b)
{
    return a + b;
}

TEST(TestTest, add)
{
    EXPECT_EQ(add(10, 5), 15);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}