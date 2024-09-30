#ifndef SORT_H
#define SORT_H

#include "../common/common.h"
#include "../heap/heap.h"
#include <algorithm>
#include <tuple>

namespace Sort {
    //void bubbleSort(int arr[], int size);
template<typename T>
class Sort : public NoCopyAble {
public:
    void selectionSort(T arr[], int n)
    {
        for (int i = 0; i < n; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < n; ++j) { // 不能提前退出
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            std::swap(arr[i], arr[minIndex]);
        }
    }

    void insertionSort(T arr[], int n)
    {
        // for (int i = 1; i < n; ++i) {
        //     T e = arr[i];
        //     int j = i;
        //     for (; (j > 0) && (arr[j - 1] > e); --j) {
        //         arr[j] = arr[j - 1]; // 少量交换
        //     }
        //     arr[j] = e;
        // }
        insertionSort(arr, 0, n - 1);
    }

    void mergeSort(T arr[], int n)
    {
        mergeSort(arr, 0, n - 1);
    }

    void quickSort(T arr[], int n)
    {
        srand(time(NULL));
        quickSort(arr, 0, n - 1);
    }

    void quickSort3ways(T arr[], int n)
    {
        srand(time(NULL));
        quickSort3ways(arr, 0, n - 1);
    }

    void heapSort1(T arr[], int n)
    {
        HEAP::Heap<T> heap(n);
        for (int i = 0; i < n; ++i) {
            heap.push(arr[i]);
        }

        // for (int i = 0; i < n; ++i) {
        //     arr[n - i - 1] = heap.pop();
        // }

        for (int i = n - 1; i >= 0; --i) {
            arr[i] = heap.pop();
        }
    }

    void heapSort2(T arr[], int n)
    {
        HEAP::Heap<T> heap(arr, n);
        for (int i = n - 1; i >= 0; --i) {
            arr[i] = heap.pop();
        }
    }

    // 数组原地排序，最大堆实现升序，最小堆实现降序
    void heapSort(T arr[], int n)
    {
        // 建堆，从最后一个非叶子节点往前进行shiftDown操作
        for (int i = (n - 1 - 1) / 2; i >= 0; --i) {
            shiftDown(i, arr, n, CmpLess<T>());
        }

        // 排序
        for (int i = n - 1; i > 0; --i) {
            std::swap(arr[0], arr[i]);
            shiftDown(0, arr, i, CmpLess<T>());
        }
    }

private:
    void insertionSort(T arr[], int l, int r)
    {
        for (int i = l + 1; i <= r; ++i) {
            int j = i;
            T e = arr[i];
            for (;(j > l) && (arr[j - 1] > e); --j) { // 可以提前退出
                arr[j] = arr[j - 1];
            }
            arr[j] = e;
        }
    }

    void shiftDown(int i, T arr[], int n, CmpLess<T> cmp)
    {
        int j = 2 * i + 1;
        while (j < n) {
            if ((j + 1 < n) && (cmp(arr[j], arr[j + 1]))) {
                j = j + 1;
            }
            if (!cmp(arr[i], arr[j])) {
                break;
            }
            std::swap(arr[i], arr[j]);
            i = j;
            j = 2 * i + 1;
        }
    }

    // 对arr[l...r]范围进行归并
    void mergeSort(T arr[], int l, int r)
    {
        // if (l >= r) {
        //     return;
        // }

        // 优化：
        if (r - l <= 15) {
            insertionSort(arr, l, r);
            return;
        }

        int mid = l + ((r -l) >> 1);
        mergeSort(arr, l, mid);
        mergeSort(arr, mid + 1, r);
        // 优化：近乎有序的数组
        if (arr[mid] > arr[mid + 1]) {
            merge(arr, l, mid, r);
        }
    }

    // 归并 arr[l...mid] 和 arr[mid+1...r]
    void merge(T arr[], int l, int mid, int r)
    {
        T *tmp = new T[r - l + 1];
        for (int i = l; i <= r; ++i) {
            tmp[i - l] = arr[i];
        }

        int i = l;
        int j = mid + 1;
        for (int k = l; k <= r; ++k) {
            if (i > mid) {
                arr[k] = tmp[j - l];
                ++j;
                continue;
            }

            if (j > r) {
                arr[k] = tmp[i - l];
                ++i;
                continue;
            }

            if (tmp[i - l] < tmp[j - l]) {
                arr[k] = tmp[i - l];
                ++i;
                continue;
            }

            arr[k] = tmp[j - l];
            ++j;
        }

        delete [] tmp;
        tmp = nullptr;
    }

    // 对arr[l...r]进行快速排序
    void quickSort(T arr[], int l, int r)
    {
        // if (l >= r) {
        //     return;
        // }

        if (r - l <= 15) {
            insertionSort(arr, l, r);
            return;
        }

        //int p = partition1(arr, l, r); // 大量重复元素的时候退化成O(n*n)
        int p = partition2(arr, l, r); // 将相同元素分散到两个分支
        quickSort(arr, l, p - 1);
        quickSort(arr, p + 1, r);
    }

    int partition1(T arr[], int l, int r)
    {
        int index = rand() % (r - l + 1) + l;
        std::swap(arr[index], arr[l]); // 以第l个元素为准

        // arr[l+1...j] < arr[l], arr[j+1, i - 1] >= arr[l]
        int j = l;
        for (int i = l + 1; i <= r; ++i) {
            if (arr[i] < arr[l]) {
                std::swap(arr[j + 1], arr[i]);
                ++j;
            }
        }

        std::swap(arr[l], arr[j]);
        return j;
    }

    int partition2(T arr[], int l, int r)
    {
        int index = rand() % (r - l + 1) + l;
        std::swap(arr[index], arr[l]);
        // arr[l+1....i-1] <= arr[l], arr[j+1...r] >= arr[l]
        int i = l + 1;
        int j = r;
        while (true) {
            while ((i <= j) && (arr[i] < arr[l])) {
                ++i;
            }
            while ((i <= j) && (arr[j] > arr[l])) {
                --j;
            }

            if (i > j) {
                break;
            }

            std::swap(arr[i], arr[j]);
            ++i;
            --j;
        }

        std::swap(arr[l], arr[j]);
        return j;
    }

    void quickSort3ways(T arr[], int l, int r) {
        if (r - l <= 15) {
            insertionSort(arr, l, r);
            return;
        }

        auto [lt, gt] = partition3ways(arr, l, r);
        quickSort3ways(arr, l, lt);
        quickSort3ways(arr, gt, r);
    }

    std::tuple<int, int> partition3ways(T arr[], int l, int r) {
        int index = rand() % (r - l + 1) + l;
        std::swap(arr[index], arr[l]);
        int lt = l;
        int gt = r + 1;
        int i = l + 1;
        while (i < gt) {
            if (arr[i] == arr[l]) {
                ++i;
                continue;
            }
            if (arr[i] < arr[l]) {
                std::swap(arr[i], arr[lt + 1]);
                ++lt;
                ++i;
                continue;
            }
            if (arr[i] > arr[lt]) {
                std::swap(arr[i], arr[gt - 1]);
                --gt;
                continue;
            }
        }

        std::swap(arr[l], arr[lt]);
        return std::make_tuple(lt - 1, gt);
    }
};

}

#endif