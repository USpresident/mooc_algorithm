#include <gtest/gtest.h>
#include <tuple>
using namespace std;

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

struct SUB {
    int a;
    int b;
    int c;

    SUB(int x, int y, int z) : a(x), b(y), c(z) {}
};

class AddTestWithPara : public ::testing::TestWithParam<tuple<int, int, int>> {};

class SubTestWithPara : public ::testing::TestWithParam<SUB> {};

TEST_P(AddTestWithPara, test)
{
    auto para = GetParam();
    EXPECT_EQ(add(get<0>(para), get<1>(para)), get<2>(para));
}

TEST_P(SubTestWithPara, test)
{
    auto para = GetParam();
    EXPECT_EQ(sub(para.a, para.b), para.c);
}

TEST(AddSubTest, test)
{
    EXPECT_EQ(add(100, 50), 150);
    EXPECT_EQ(sub(100, 50), 50);
}

// INSTANTIATE_TEST_CASE_P 和 INSTANTIATE_TEST_SUITE_P 一样
// INSTANTIATE_TEST_CASE_P(AddTest, AddTestWithPara,
//     ::testing::Values((tuple<int, int, int> {1, 2, 3}),
//     (tuple<int, int, int> {10, 2, 12}), (tuple<int, int, int>{15, 20, 35})));

INSTANTIATE_TEST_SUITE_P(AddTest, AddTestWithPara,
    ::testing::Values((tuple<int, int, int> {1, 2, 3}),
    (tuple<int, int, int> {10, 2, 12}), (tuple<int, int, int>{15, 20, 35})));

INSTANTIATE_TEST_CASE_P(SubTest, SubTestWithPara,
    ::testing::Values(SUB(3, 2, 1), SUB(20, 10, 10), SUB(5, 6, -1)));

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

