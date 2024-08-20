#ifndef WEIGHTED_DENSE_GRAPH_H
#define WEIGHTED_DENSE_GRAPH_H

#include <cassert>
#include <vector>
#include <iomanip> // setprecision
#include "edge.h"
#include "../common/common.h"

namespace WEIGHTED_GRAPH {

template<typename Weight>
class DenseGraph : public NoCopyAble {
private:
    int m_vNum;
    int m_eNum;
    bool m_directed;
    std::vector<std::vector<Edge<Weight> *>> m_graph; // 存指针是方便表示邻接矩阵中两节点没有边连接

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

    Edge<Weight> *begin()
    {
        m_index = -1;
        return next();
    }

    Edge<Weight> *next()
    {
        for (++m_index; m_index < m_graph.m_graph[m_vertex].size(); ++m_index) {
            if (m_graph.m_graph[m_vertex][m_index] != nullptr) {
                return m_graph.m_graph[m_vertex][m_index];
            }
        }
        return nullptr;
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
        m_graph.resize(vNum, std::vector<Edge<Weight> *>(vNum, nullptr));
    }

    ~DenseGraph()
    {
        for (int i = 0; i < m_vNum; ++i) {
            for (int j = 0; j < m_vNum; ++j) {
                if (m_graph[i][j] != nullptr) {
                    delete m_graph[i][j];
                }
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

    /**
     * @brief 节点v1到节点v2是否存在边
     */
    bool hasEdge(int v1, int v2) const
    {
        assert(v1 >= 0 && v1 < m_vNum);
        assert(v2 >= 0 && v2 < m_vNum);
        return m_graph[v1][v2] != nullptr;
    }

    /**
     * @brief 添加节点v1到节点v2的一条边
     */
    void addEdge(int v1, int v2, Weight weight)
    {
        // 去掉了平行边(重复边，代价可能不一样，可覆盖，可跳过，按需)
        if (hasEdge(v1, v2)) {
            return;
        }

        m_graph[v1][v2] = new Edge<Weight>(v1, v2, weight);
        if (!m_directed) {
            m_graph[v2][v1] = new Edge<Weight>(v2, v1, weight);;
        }

        ++m_eNum;
    }

    void showGraph() const
    {
        // 固定的小数点位数fixed, 小数精度setprecision(), setw()宽度
        std::cout << fixed << setprecision(2);

        std::cout << "Adjacency matrix is:" << std::endl;
        for (int i = 0; i < m_vNum; ++i) {
            for (int j = 0; j < m_vNum; ++j) {
                if (m_graph[i][j] != nullptr) {
                    std::cout << m_graph[i][j]->getEdgeWeight(); // Weight支持 <<
                } else {
                    std::cout << "NULL";
                }

                if (j == m_vNum - 1) {
                    std::cout << std::endl;
                } else {
                    std::cout << "   ";
                }
            }
        }

    }

};
}

#endif