#ifndef SPARSE_GRAPH_H
#define SPARSE_GRAPH_H

#include <vector>
#include <cassert>
#include <algorithm>

#include "../common/common.h"

namespace GRAPH {

class SparseGraph : public NoCopyAble {
private:
    int m_vNum;
    int m_eNum;
    bool m_directed;
    std::vector<std::vector<int>> m_graph; // 第一维表示节点ID，第二维表示节点的邻边

public:
class iterator {
private:
    SparseGraph &m_graph; // 引用要使用初始化列表来构造
    int m_vertex;
    int m_index; // 当前遍历到的位置
public:
    iterator(SparseGraph &graph, int vertex) : m_graph(graph)
    {
        m_vertex = vertex;
        m_index = 0;
    }

    int begin()
    {
        m_index = 0;
        return (m_graph.m_graph[m_vertex].size() != 0) ?
            m_graph.m_graph[m_vertex][m_index] : -1;
    }

    int next()
    {
        ++m_index;
        return (m_index < m_graph.m_graph[m_vertex].size()) ?
            m_graph.m_graph[m_vertex][m_index]: -1;
    }

    bool end()
    {
        return m_index >= m_graph.m_graph[m_vertex].size();
    }

};

public:
    SparseGraph(int vNum, int direct = false)
    {
        m_vNum = vNum;
        m_eNum = 0;
        m_directed = direct;
        m_graph.resize(vNum, std::vector<int>()); // 第二维初始化为空向量
    }

    ~SparseGraph() = default;

    int getVertexNum() const
    {
        return m_vNum;
    }

    int getEdgeNum() const
    {
        return m_eNum;
    }

    bool hasEdge(int v1, int v2) const
    {
        assert(v1 >= 0 && v1 < m_vNum);
        assert(v2 >= 0 && v2 < m_vNum);
        return std::find(m_graph[v1].begin(), m_graph[v1].end(), v2) != m_graph[v1].end();
    }

    void addEdge(int v1, int v2)
    {
        // 复杂度为O(n)，用邻接表表示图先不管平行边；可以先加入所有边最后去除平行边
        // if (hasEdge(v1, v2)) {
        //     return;
        // }

        assert(v1 >= 0 && v1 < m_vNum);
        assert(v2 >= 0 && v2 < m_vNum);

        m_graph[v1].push_back(v2);
        if ((v1 != v2) && (!m_directed)) { // 自环边只加一次，v1 != v2
            m_graph[v2].push_back(v1);
        }

        ++m_eNum;
    }

};
}

#endif