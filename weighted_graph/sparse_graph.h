#ifndef WEIGHTED_SPARSE_GRAPH_H
#define WEIGHTED_SPARSE_GRAPH_H

#include <vector>
#include <cassert>
#include <algorithm>
#include <iomanip>
#include "edge.h"
#include "../common/common.h"

namespace WEIGHTED_GRAPH {

template <typename Weight>
class SparseGraph : public NoCopyAble {
private:
    int m_vNum;
    int m_eNum;
    bool m_directed;
    std::vector<std::vector<Edge<Weight> *>> m_graph; // 第一维表示节点ID，第二维表示节点的邻边

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

    Edge<Weight> *begin()
    {
        m_index = 0;
        return (m_graph.m_graph[m_vertex].size() != 0) ?
            m_graph.m_graph[m_vertex][m_index] : nullptr;
    }

    Edge<Weight> *next()
    {
        ++m_index;
        return (m_index < m_graph.m_graph[m_vertex].size()) ?
            m_graph.m_graph[m_vertex][m_index] : nullptr;
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
        m_graph.resize(vNum, std::vector<Edge<Weight> *>()); // 第二维初始化为空向量
    }

    ~SparseGraph()
    {
        for (int i = 0; i < m_vNum; ++i) {
            for (int j = 0; j < m_graph[i].size(); ++j) {
                delete m_graph[i][j]; // delete nullptr 也OK
            }
        }
    }

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
        
        for (int i = 0; i < m_graph[v1].size(); ++i) {
            if (m_graph[v1][i]->getAnotherVertex(v1) == v2) {
                return true;
            }
        }

        return false;
    }

    void addEdge(int v1, int v2, Weight weight)
    {
        // 复杂度为O(n),测试数据没有平行边，先不处理
        // if (hasEdge(v1, v2)) {
        //     return;
        // }

        assert(v1 >= 0 && v1 < m_vNum);
        assert(v2 >= 0 && v2 < m_vNum);

        m_graph[v1].push_back(new Edge(v1, v2, weight));
        if ((v1 != v2) && (!m_directed)) { // 自环边只加一次，v1 != v2
            m_graph[v2].push_back(new Edge(v2, v1, weight));
        }

        ++m_eNum;
    }

    void showGraph()
    {
        std::cout << fixed << setprecision(2);
        for (int i = 0; i < m_vNum; ++i) {
            std::cout << "vertex " << i << " :";
            for (int j = 0; j < m_graph[i].size(); ++j) {
                std::cout << *m_graph[i][j];
                if (j == m_graph[i].size() - 1) {
                    std::cout << std::endl;
                } else {
                    std::cout << " ";
                }
            }
        }
    }

};
}

#endif