#ifndef COMPONENT_H
#define COMPONENT_H

#include "../common/common.h"

// 图的深度优先遍历

namespace GraphAlgorithm {

template <typename Graph>
class Component : public NoCopyAble {
public:
    Component(Graph &graph) : m_graph(graph)
    {
        m_componentCount = 0;
        m_componentId = new int[graph.getVertexNum()];
        m_isvisited = new bool[graph.getVertexNum()];
        for (int i = 0; i < graph.getVertexNum(); ++i) {
            m_componentId[i] = -1;
            m_isvisited[i] = false;
        }
    }

    virtual ~Component(){
        delete[] m_componentId;
        delete[] m_isvisited;
    }

    /**
     * @brief 计算图的连通分量
     * @return 图的连通分量个数 
     */
    int componentCount()
    {
        for (int i = 0; i < m_graph.getVertexNum(); ++i) {
            if (m_isvisited[i]) {
                continue;
            }

            dfs(i); // 深度优先搜索
            ++m_componentCount;
        }

        return m_componentCount;
    }

private:
    void dfs(int i)
    {
        m_isvisited[i] = true;
        m_componentId[i] = m_componentCount;
        typename Graph::iterator it(m_graph, i);
        for (int k = it.begin(); !it.end(); k = it.next()) {
            if (!m_isvisited[k]) {
                dfs(k);
            }
        }
    }

private:
    Graph &m_graph;
    bool *m_isvisited;
    int *m_componentId; // 链路分量的ID
    int m_componentCount; // 连通分量的个数
};
}

#endif