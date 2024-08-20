#ifndef QUICK_UNION_OPTIM2_H
#define QUICK_UNION_OPTIM2_H

#include<cassert>
#include "../common/common.h"

namespace UNION_FIND
{

class QuickUnionOptimByRank : public NoCopyAble {
public:
    QuickUnionOptimByRank(int n) {
        m_parent = new int[n];
        m_rank = new int[n];
        for (int i = 0; i < n; ++i) {
            m_parent[i] = i;
            m_rank[i] = 1;
        }
        m_count = n;
    }

    virtual ~QuickUnionOptimByRank()
    {
        delete [] m_parent;
        delete [] m_rank;
    }

    int find(int p)
    {
        assert((p >= 0) && (p < m_count));
        while (m_parent[p] != p) {
            m_parent[p] = m_parent[m_parent[p]]; // 路径压缩，将p的父节点的父节点作为p的父节点
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

        // 层数少的集合指向层数多的集合
        if (m_rank[pRoot] < m_rank[qRoot]) {
            m_parent[pRoot] = qRoot;
        } else if (m_rank[pRoot] > m_rank[qRoot]){
            m_parent[qRoot] = pRoot;
        } else {
            m_parent[qRoot] = pRoot;
            ++m_rank[pRoot];
        }
    }

private:
    int *m_parent; // 索引表示节点元素，值表示节点的父节点
    int *m_rank; // m_rank[i]表示以i为根的集合表示的树的层数
    int m_count;
};

}

#endif