#include <gtest/gtest.h>
#include "../sort/sort.h"
#include "../sort/sort_test_help.h"
#include <iostream>

class SortTestClass : public ::testing::Test {
public:
    int getNum()
    {
        return m_num;
    }

    int *getArr()
    {
        return m_arr;
    }

    Sort::Sort<int> &getObj()
    {
        return m_obj;
    }

private:
    virtual void SetUp()
    {
        m_num = 1000000;
        m_arr = SortTestHelper::generateRandomArray(m_num, 0, m_num*10);
        std::cout << "init success..." << std::endl;
    }

    virtual void TearDown()
    {
        delete [] m_arr;
        m_arr = nullptr;
        std::cout << "end success..." << std::endl;
    }

private:
    int m_num;
    int *m_arr;
    Sort::Sort<int> m_obj;
};

TEST_F(SortTestClass, mergeSort)
{
    bool res = SortTestHelper::testSort1("mergeSort", getObj(),
        &Sort::Sort<int>::mergeSort, getArr(), getNum());
    EXPECT_TRUE(res);
}

TEST_F(SortTestClass, quickSort)
{
    bool res = SortTestHelper::testSort1("quickSort", getObj(),
        &Sort::Sort<int>::quickSort, getArr(), getNum());
    EXPECT_TRUE(res);
}

TEST_F(SortTestClass, quickSort3ways)
{
    bool res = SortTestHelper::testSort1("quickSort3ways", getObj(),
        &Sort::Sort<int>::quickSort3ways, getArr(), getNum());
    EXPECT_TRUE(res);
}

TEST_F(SortTestClass, heapSort1)
{
    bool res = SortTestHelper::testSort1("heapSort1", getObj(),
        &Sort::Sort<int>::heapSort1, getArr(), getNum());
    EXPECT_TRUE(res);
}

TEST_F(SortTestClass, heapSort2)
{
    bool res = SortTestHelper::testSort1("heapSort2", getObj(),
        &Sort::Sort<int>::heapSort2, getArr(), getNum());
    EXPECT_TRUE(res);
}

TEST_F(SortTestClass, heapSort)
{
    bool res = SortTestHelper::testSort1("heapSort", getObj(),
        &Sort::Sort<int>::heapSort, getArr(), getNum());
    EXPECT_TRUE(res);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}