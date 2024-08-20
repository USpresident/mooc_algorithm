#ifndef DENSE_GRAPH_H
#define DENSE_GRAPH_H

#include "../common/common.h"

#include <cassert>
#include <vector>

namespace GRAPH {
class DenseGraph : public NoCopyAble {
private:
    int m_vNum;
    int m_eNum;
    bool m_directed;
    std::vector<std::vector<bool>> m_graph;

public:
class iterator {
private:
    DenseGraph &m_graph;
    int m_vertex;
    int m_index;
public:
    iterator(DenseGraph &graph, int vertex) : m_graph(graph)
    {
        m_vertex = vertex;
        m_index = -1;
    }

    int begin()
    {
        m_index = -1;
        return next();
    }

    int next()
    {
        for (++m_index; m_index < m_graph.m_graph[m_vertex].size(); ++m_index) {
            if (m_graph.m_graph[m_vertex][m_index]) {
                return m_index;
            }
        }
        return -1;
    }

    bool end()
    {
        return m_index >= m_graph.m_graph[m_vertex].size();
    }
};

public:
    DenseGraph(int vNum, bool directed = false)
    {
        m_vNum = vNum;
        m_eNum = 0;
        m_directed = directed;
        m_graph.resize(vNum, std::vector<bool>(vNum, false));
    }

    ~DenseGraph() = default;

    int getVertexNum() const
    {
        return m_vNum;
    }

    int getEdgeNum() const
    {
        return m_eNum;
    }

    /**
     * @brief 节点v1到节点v2是否存在边
     */
    bool hasEdge(int v1, int v2) const
    {
        assert(v1 >= 0 && v1 < m_vNum);
        assert(v2 >= 0 && v2 < m_vNum);
        return m_graph[v1][v2];
    }

    /**
     * @brief 添加节点v1到节点v2的一条边
     */
    void addEdge(int v1, int v2)
    {
        // 去掉了平行边
        if (hasEdge(v1, v2)) {
            return;
        }

        m_graph[v1][v2] = true;
        if (!m_directed) {
            m_graph[v2][v1] = true;
        }

        ++m_eNum;
    }

};
}

#endif