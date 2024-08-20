#ifndef INDEX_HEAP_H
#define INDEX_HEAP_H

#include <cassert>
#include "../common/common.h"

namespace HEAP {

template<typename T, typename CMP = CmpLess<T>>
class IndexHeap : public NoCopyAble {
public:
    IndexHeap(int capacity) : m_capacity(capacity), m_size(0),
        m_index(new int[capacity + 1]{}), m_data(new T[capacity + 1]{}) {
        m_rvsIndex = new int[capacity + 1];
        for (int i = 0; i <= capacity; i++) {
            m_rvsIndex[i] = 0; // 内部下标从1开始，0无意义，初始时i在m_index的无效位置
        }
    }

    ~IndexHeap()
    {
        delete[] m_index;
        delete[] m_data;
        delete[] m_rvsIndex;
    }

    int size() const
    {
        return m_size;
    }

    bool isEmpty() const
    {
        return m_size == 0;
    }

    /**
     * @brief 堆中是否包含索引i
     */
    bool contains(int i) const
    {
        if ((i < 0) || (i + 1 > m_capacity)) {
            return false;
        }
        return m_rvsIndex[i + 1] != 0;
    }

    /**
     * @brief 当前有问题，指定重复的i,m_data和rvsIndex更新，一份data对应堆的多个index；
     *        入堆时不能有重复的i（不能通过contains来判断，因为堆中有重复的i）;
     *        使用的时候i从0开始顺序指定即可
     */
    void push(int i, T elem) // 外部传入i从0开始，内部实现从1开始
    {
        assert(m_size + 1 <= m_capacity);
        assert((i >= 0) && (i + 1 <= m_capacity));

        i += 1; // 内部实现从1开始

        // 元素数据的位置随意指定，但是索引数组必须是紧密的（满足完全二叉树）
        m_data[i] = elem; // ?? 如果i位置已有元素，m_size不应该++
        m_index[++m_size] = i;
        m_rvsIndex[i] = m_size; // 置为m_size，表示i位置有元素

        shiftUp(m_size, CMP());
    }

    T pop()
    {
        assert(!isEmpty());
        T elem = std::move(m_data[m_index[1]]);
        std::swap(m_index[1], m_index[m_size]);
        m_rvsIndex[m_index[m_size]] = 0; // 置为0，表示i位置已无元素
        --m_size;

        if (m_size >= 1) {
            m_rvsIndex[m_index[1]] = 1;
            shiftDown(1, CMP());
        }
        
        return elem;
    }

    int popTopElemIndex()
    {
        assert(!isEmpty());

        int index = m_index[1] - 1;
        std::swap(m_index[1], m_index[m_size]);
        m_rvsIndex[m_index[m_size]] = 0; // 置为0，表示i位置已无元素
        --m_size;

        if (m_size >= 1) {
            m_rvsIndex[m_index[1]] = 1;
            shiftDown(1, CMP());
        }

        return index;
    }

    int getTopElem()
    {
        assert(!isEmpty());
        return m_data[m_index[1]];
    }

    int getElem(int i)
    {
        assert(contains(i));
        return m_data[i + 1];
    }

    int getTopElemIndex()
    {
        assert(!isEmpty());
        return m_index[1] - 1; // 0-based index
    }

    /**
     * @brief 在没有重复元素的情况下更新元素
     */
    void change(int i, T elem)
    {
        if (!contains(i)) {
            return;
        }

        i += 1;
        m_data[i] = elem;
        int j = m_rvsIndex[i]; // 要求堆中没有重复索引
        shiftDown(j, CMP());
        shiftUp(j, CMP());
    }

    T getData(int i)
    {
        assert(contains(i));
        return m_data[i + 1];
    }

    void printHeap()
    {
        std::cout << "data in orig: ";
        for (int i = 1; i <= m_size; ++i) {
            std::cout << m_data[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "data in heap: ";
        for (int i = 1; i <= m_size; ++i) {
            std::cout << m_data[m_index[i]] << " ";
        }
        std::cout << std::endl;        
    }

private:
    void shiftUp(int k, CMP cmp)
    {
        while ((k > 1) && cmp(m_data[m_index[k / 2]], m_data[m_index[k]])) {
            std::swap(m_index[k / 2], m_index[k]);
            m_rvsIndex[m_index[k]] = k;
            m_rvsIndex[m_index[k / 2]] = k / 2;
            k /= 2;
        }
    }

    void shiftDown(int k, CMP cmp)
    {
        int j = 2 * k;
        while (j <= m_size) {
            if ((j + 1 <= m_size) && cmp(m_data[m_index[j]], m_data[m_index[j + 1]])) {
                j += 1;
            }

            if (!cmp(m_data[m_index[k]], m_data[m_index[j]])) {
                break;
            }

            std::swap(m_index[k], m_index[j]);
            m_rvsIndex[m_index[k]] = k;
            m_rvsIndex[m_index[j]] = j;

            k = j;
            j *= 2;
        }
    }

private:
    int m_capacity;
    int m_size;
    int *m_index; // 数据的索引用于建堆。m_index[j] = i;表示堆中j位置存放的是索引i;
    int *m_rvsIndex; // m_rvsIndex[i] = j; 表示索引i在index堆中的位置是j
    T *m_data;
};

}


#endif