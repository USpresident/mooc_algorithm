#ifndef QUICK_UNION_H
#define QUICK_UNION_H

#include<cassert>
#include "../common/common.h"

namespace UNION_FIND
{

class QuickUnion : public NoCopyAble {
public:
    QuickUnion(int n) {
        m_parent = new int[n];
        for (int i = 0; i < n; ++i) {
            m_parent[i] = i;
        }
        m_count = n;
    }

    virtual ~QuickUnion()
    {
        delete [] m_parent;
    }

    int find(int p)
    {
        assert((p >= 0) && (p < m_count));
        while (m_parent[p] != p) {
            p = m_parent[p];
        }
        return p;
    }

    bool isConnected(int p, int q)
    {
        return find(p) == find(q);
    }

    void unionElements(int p, int q)
    {
        int pRoot = find(p);
        int qRoot = find(q);
        if (pRoot == qRoot) {
            return;
        }

        m_parent[pRoot] = qRoot; // 高度不保障最优
    }

private:
    int *m_parent; // 将元素视为节点，索引表示节点元素，值表示节点的父节点
    int m_count;
};

}

#endif