#ifndef UNION_FIND_H

#define UNION_FIND_H

#include <cassert>
#include<iostream>
#include "../common/common.h"

namespace UNION_FIND
{

class UnionFind : public NoCopyAble {
public:
    UnionFind(int n)
    {
        m_id = new int[n];
        m_count = n;
        for (int i = 0; i < n; ++i) {
            m_id[i] = i;
        }
    }

    virtual ~UnionFind()
    {
        delete [] m_id;
    }

    int find(int p)
    {
        assert((p >= 0) && (p < m_count));
        return m_id[p];
    }

    int count() const
    {
        return m_count;
    }

    bool isConnected(int x, int y)
    {
        return find(x) == find(y);
    }

    void unionElements(int p, int q)
    {
        int pId = find(p);
        int qId = find(q);
        if (pId == qId) {
            return;
        }

        // 时间复杂度O(n)
        for (int i = 0; i < m_count; ++i) {
            if (m_id[i] == pId) {
                m_id[i] = qId;
            }
        }
    }

private:
    int *m_id; // 数组索引表示元素，数组内容表示元素所在组ID，相同组ID的元素是连接在一起的
    int m_count;
};

}

#endif