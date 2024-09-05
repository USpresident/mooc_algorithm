#include <gtest/gtest.h>
#include <iostream>
using namespace std;

int add(int a, int b)
{
    return a + b;
}

class AddTestClass : public ::testing::Test {
public:
    AddTestClass()
    {
        cout << "AddTestClass" << endl;
    }

    ~AddTestClass()
    {
        cout << "~AddTestClass" << endl;
    }

    static void SetUpTestCase() // SetUpTestSuite
    {
        cout << "---------SetUpTestCase" << endl;
    }

    static void TearDownTestCase()
    {
        cout << "---------TearDownTestCase" << endl;
    }

    virtual void SetUp()
    {
        cout << "SetUp..." << endl;
    }

    virtual void TearDown()
    {
        cout << "TearDown..." << endl;
    }
};


TEST_F(AddTestClass, test)
{
    EXPECT_EQ(add(7, 3), 11);
}

TEST_F(AddTestClass, test2)
{
    cout << __FUNCTION__ << endl;
    EXPECT_EQ(add(7, 13), 20);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}