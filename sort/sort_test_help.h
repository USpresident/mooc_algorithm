#ifndef SORT_TEST_HELP_H
#define SORT_TEST_HELP_H

#include <iostream>
#include <ctime>
#include <cassert>
#include "sort.h"

using namespace std;

namespace SortTestHelper {

    template <typename T>
    void PrintArray(T arr[], int n)
    {
        for (int i = 0; i < n; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    template <typename T>
    bool isSorted(T arr[], int n)
    {
        for (int i = 0; i < n - 1; ++i) {
            if (arr[i] > arr[i + 1]) {
                return false;
            }
        }
        return true;
    }

    template <typename T>
    void testSort(string sortName, Sort::Sort<T> &obj, void (Sort::Sort<T>::*sort)(T[], int), T arr[], int n) {
        assert(n > 0);
        clock_t startTime = clock();
        (obj.*sort)(arr, n);
        clock_t endTime = clock();

        // PrintArray(arr, n);

        assert(isSorted(arr, n));

        double elapsedTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
        cout << sortName << " taken: " << elapsedTime << " seconds." << endl;
    }

    template <typename T>
    bool testSort1(string sortName, Sort::Sort<T> &obj, void (Sort::Sort<T>::*sort)(T[], int), T arr[], int n) {
        assert(n > 0);
        clock_t startTime = clock();
        (obj.*sort)(arr, n);
        clock_t endTime = clock();

        // PrintArray(arr, n);

        // assert(isSorted(arr, n));
        if (isSorted(arr, n)) {
            return true;
        }

        double elapsedTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
        cout << sortName << ", " << n << " elems, taken: " << elapsedTime << " seconds." << endl;

        return false;
    }

    int *generateRandomArray(int n, int rangeL, int rangeR)
    {
        assert(rangeL <= rangeR);
        assert(n > 0);
        srand(time(NULL));
        // Generate a random array with elements in [rangeL, rangeR]
        int *arr = new int[n];
        for (int i = 0; i < n; ++i) {
            arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
        }
        return arr;
    }

    int *generateNearlyOrderedArray(int n, int sawpTimes)
    {
        assert(n > 0);
        srand(time(NULL));
        int *arr = new int[n];
        for (int i = 0; i < n; ++i) {
            arr[i] = i;
        }

        for (int i = 0; i < sawpTimes; ++i) {
            int index1 = rand() % n;
            int index2 = rand() % n;
            swap(arr[index1], arr[index2]);
        }

        return arr;
    }

    int *copyIntArray(int arr[], int n)
    {
        int *copyArr = new int[n];
        // for (int i = 0; i < n; ++i) {
        //     copy[i] = arr[i];
        // }

        copy(arr, arr + n, copyArr);
        return copyArr;
    }
}

#endif