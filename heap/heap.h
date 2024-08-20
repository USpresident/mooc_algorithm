#ifndef HEAP_H
#define HEAP_H

#include <cassert>
#include "../common/common.h"

namespace HEAP {

// CMP是比较器，入参顺序决定：CmpLess 是最大堆，CmpGreater 是最小堆
template <typename T, typename CMP = CmpLess<T>>
class Heap : public NoCopyAble{
public:
    Heap(int capacity) : m_capacity(capacity)
    {
        m_data = new T[capacity + 1];
        m_size = 0;
        m_capacity = capacity;
    }

    // 将数组直接构建成堆
    Heap(T arr[], int n) {
        m_data = new T[n + 1];
        m_capacity = n;
        for (int i = 0; i < n; i++) {
            m_data[i + 1] = arr[i];
        }
        m_size = n;

        for (int i = m_size / 2; i >= 1; --i) {
            shiftDown(i, CMP());
        }
    }

    Heap(const Heap &) = delete;
    Heap(const Heap &&) = delete;

    ~Heap()
    {
        delete[] m_data;
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    int size() const
    {
        return m_size;
    }

    bool isEmpty() const
    {
        return (m_size == 0);
    }

    void push(T elem)
    {
        if (m_size + 1 > m_capacity) {
            // cout << "Heap is full!" << endl;
            return;
        }

        m_data[++m_size] = elem;
        shiftUp(m_size, CMP());
    }

    T pop()
    {
        assert(!isEmpty());

        T elem = m_data[1];
        std::swap(m_data[1], m_data[m_size--]);
        shiftDown(1, CMP());

        return elem;
    }

private:
    void shiftUp(int i, CMP cmp)
    {
        while ((i > 1) && cmp(m_data[i / 2], m_data[i])) {
            std::swap(m_data[i / 2], m_data[i]); // 可以优化：找到合适位置再交换
            i /= 2;
        }
    }

    void shiftDown(int i, CMP cmp)
    {
        int j = 2 * i;
        while (j <= m_size) {
            if ((j + 1 <= m_size) && (cmp(m_data[j], m_data[j + 1]))) {
                j += 1;
            }

            if (!cmp(m_data[i], m_data[j])) {
                break;
            }

            std::swap(m_data[i], m_data[j]); // 可以优化：找到合适位置再交换
            i = j;
            j = 2 * i;
        }
    }

private:
    T *m_data{nullptr};
    int m_capacity{};
    int m_size{};
};

}


#endif