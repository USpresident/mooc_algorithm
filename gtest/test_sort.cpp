#include <gtest/gtest.h>
#include "../sort/sort.h"
#include "../sort/sort_test_help.h"

TEST(Sort, selectionSort)
{
    int n = 100000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n*10);

    Sort::Sort<int> obj;
    bool res = SortTestHelper::testSort1("insertionSort", obj, &Sort::Sort<int>::insertionSort, arr, n);

    EXPECT_TRUE(res);

    delete [] arr;
}

TEST(Sort, insertionSort)
{
    int n = 100000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n*10);

    Sort::Sort<int> obj;
    bool res = SortTestHelper::testSort1("insertionSort", obj, &Sort::Sort<int>::insertionSort, arr, n);

    EXPECT_TRUE(res);

    delete [] arr;
}

TEST(Sort, mergeSort)
{
    int n = 1000000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n*10);

    Sort::Sort<int> obj;
    bool res = SortTestHelper::testSort1("mergeSort", obj, &Sort::Sort<int>::mergeSort, arr, n);

    EXPECT_TRUE(res);

    delete [] arr;
}

TEST(Sort, quickSort)
{
    int n = 1000000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n*10);

    Sort::Sort<int> obj;
    bool res = SortTestHelper::testSort1("quickSort", obj, &Sort::Sort<int>::quickSort, arr, n);

    EXPECT_TRUE(res);

    delete [] arr;
}

TEST(Sort, quickSort3ways)
{
    int n = 1000000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n*10);

    Sort::Sort<int> obj;
    bool res = SortTestHelper::testSort1("quickSort3ways", obj, &Sort::Sort<int>::quickSort3ways, arr, n);

    EXPECT_TRUE(res);

    delete [] arr;
}

TEST(Sort, heapSort1)
{
    int n = 1000000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n*10);

    Sort::Sort<int> obj;
    bool res = SortTestHelper::testSort1("heapSort1", obj, &Sort::Sort<int>::heapSort1, arr, n);

    EXPECT_TRUE(res);

    delete [] arr;
}

TEST(Sort, heapSort2)
{
    int n = 1000000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n*10);

    Sort::Sort<int> obj;
    bool res = SortTestHelper::testSort1("heapSort2", obj, &Sort::Sort<int>::heapSort2, arr, n);

    EXPECT_TRUE(res);

    delete [] arr;
}

TEST(Sort, heapSort)
{
    int n = 1000000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n*10);

    Sort::Sort<int> obj;
    bool res = SortTestHelper::testSort1("heapSort", obj, &Sort::Sort<int>::heapSort, arr, n);

    EXPECT_TRUE(res);

    delete [] arr;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
