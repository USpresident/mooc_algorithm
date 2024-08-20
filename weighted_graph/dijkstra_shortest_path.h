#ifndef DIJKSTRA_SHORTEST_PATH_H
#define DIJKSTRA_SHORTEST_PATH_H

#include "../heap/index_heap.h"
#include "edge.h"
#include <vector>
#include <stack>

namespace GraphAlgorithm {

/**
 * @brief Dijkstra algorithm can't handle the case where
 *        the edge weight between two nodes is negative.
 */

template <typename Graph, typename Weight>
class DijkstraShortestPath : public NoCopyAble {
public:
    DijkstraShortestPath(Graph &graph, int source) : m_graph(graph), m_source(source)
    {
        m_distTo.resize(graph.getVertexNum(), Weight());
        m_edgeFrom.resize(graph.getVertexNum(), nullptr);
        m_marked.resize(graph.getVertexNum(), false);

        dijkstra();
    }

    ~DijkstraShortestPath()
    {
        m_distTo.clear();
        m_edgeFrom.clear();
        m_marked.clear();
    }

    Weight distTo(int i) const
    {
        assert((i >= 0) && (i < m_graph.getVertexNum()));
        return m_distTo[i];
    }

    bool hasPathTo(int i) const
    {
        assert((i >= 0) && (i < m_graph.getVertexNum()));
        return m_marked[i];
    }

    void showPathTo(int i)
    {
        std::vector<int> path = pathTo(i);
        std::cout << "Source " << m_source << " to " << i << ": ";
        for (int i = 0; i < path.size(); i++) {
            std::cout << path[i];
            if (i != path.size() - 1) {
                std::cout << " -> ";
            }
        }

        std::cout << ". dist: " << m_distTo[i] << std::endl;
    }

    void showAllPath()
    {
        for (int i = 0; i < m_graph.getVertexNum(); ++i) {
            showPathTo(i);
        }
    }

private:

    void dijkstra()
    {
        HEAP::IndexHeap<Weight, CmpGreater<Weight>> indexHeap(m_graph.getVertexNum());

        m_distTo[m_source] = Weight();
        m_marked[m_source] = true;
        indexHeap.push(m_source, m_distTo[m_source]);

        while (!indexHeap.isEmpty()) {
            // 1、取出距离s最近的节点
            int v = indexHeap.popTopElemIndex();
            m_marked[v] = true; // 表示 s 到 v 的最短路径已经计算出出来了

            // 2、遍历v的所有邻边，并进行松弛操作
            typename Graph::iterator it(m_graph, v);
            for (auto *edge = it.begin(); !it.end(); edge = it.next()) {
                int w = edge->getAnotherVertex(v);

                if (m_marked[w]) {
                    continue;
                }

                if ((m_edgeFrom[w] == nullptr) || ((m_distTo[v] + edge->getEdgeWeight()) < m_distTo[w])) {
                    m_edgeFrom[w] = edge;
                    m_distTo[w] = m_distTo[v] + edge->getEdgeWeight();
                    indexHeap.push(w, m_distTo[w]);
                } else if ((m_distTo[v] + edge->getEdgeWeight()) < m_distTo[w]) {
                    m_edgeFrom[w] = edge;
                    m_distTo[w] = m_distTo[v] + edge->getEdgeWeight();
                    indexHeap.change(w, m_distTo[w]);
                }
            }
        }
    }

    std::vector<int> pathTo(int i)
    {
        std::vector<int> res{};
        if (!hasPathTo(i)) {
            return res;
        }

        std::stack<int> stack;
        stack.push(i);
        while (i != m_source) {
            // if (m_edgeFrom[i] == nullptr) {
            //     return;
            // }

            i = m_edgeFrom[i]->getAnotherVertex(i);
            stack.push(i);
        }

        while (!stack.empty()) {
            res.emplace_back(stack.top());
            stack.pop();
        }

        return res;
    }

private:
    Graph &m_graph;
    int m_source;
    std::vector<Weight> m_distTo; // 源到每个节点的最小距离
    std::vector<WEIGHTED_GRAPH::Edge<Weight> *> m_edgeFrom;
    std::vector<bool> m_marked;
};

}

#endif