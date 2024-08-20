#ifndef QUICK_UNION_OPTIM_H
#define QUICK_UNION_OPTIM_H

#include<cassert>
#include "../common/common.h"

namespace UNION_FIND
{

class QuickUnionOptimBySize : public NoCopyAble {
public:
    QuickUnionOptimBySize(int n) {
        m_parent = new int[n];
        m_size = new int[n];
        for (int i = 0; i < n; ++i) {
            m_parent[i] = i;
            m_size[i] = 1; // 初始时，每个元素自成一个集合，集合中只有一个元素
        }
        m_count = n;
    }

    virtual ~QuickUnionOptimBySize()
    {
        delete [] m_parent;
        delete [] m_size;
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

        // 元素个数少的集合指向元素个数多的集合
        if (m_size[pRoot] < m_size[qRoot]) {
            m_parent[pRoot] = qRoot;
            m_size[qRoot] += m_size[pRoot];
        } else {
            m_parent[qRoot] = pRoot;
            m_size[pRoot] += m_size[qRoot];
        }
    }

private:
    int *m_parent; // 索引表示节点元素，值表示节点的父节点
    int *m_size; // m_size[i]表示以i为根的集合中元素个数
    int m_count;
};

}

#endif