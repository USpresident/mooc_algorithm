#ifndef LAZY_PRIM_MIN_TREE_H
#define LAZY_PRIM_MIN_TREE_H

#include "../heap/heap.h"
#include "edge.h"
#include "../common/common.h"

namespace GraphAlgorithm {

template<typename Graph, typename Weight>
class LazyPrimeMST : public NoCopyAble {
public:
    // m_mimHeap 成员对象的初始化只能在初始化列表
    LazyPrimeMST(Graph &graph) : m_graph(graph),
        m_mimHeap(HEAP::Heap<WEIGHTED_GRAPH::Edge<Weight>, CmpGreater<WEIGHTED_GRAPH::Edge<Weight>>>(m_graph.getEdgeNum()))
    {
        m_marked = new bool[graph.getVertexNum()];
        for (int i = 0; i < graph.getVertexNum(); ++i) {
            m_marked[i] = false;
        }

        lazyPrim();
    }

    ~LazyPrimeMST() {
        delete[] m_marked;
        m_mstEdges.clear();
    }

    const std::vector<WEIGHTED_GRAPH::Edge<Weight>> &getMstEdges() const {
        return m_mstEdges;
    }

    const Weight &getMstWeight() const {
        return m_mstWeight;
    }

    void showMST()
    {
        std::cout << "LazyPrimeMST weight: " << m_mstWeight << std::endl;
        for (const auto &edge : m_mstEdges) {
            std::cout << edge << std::endl;
        }
    }

private:
    void lazyPrim() {
        visit(0);

         // 优化: (m_mstEdges.size() < m_graph.getVertexNum() - 1)
        while ((!m_mimHeap.isEmpty()) && (m_mstEdges.size() < m_graph.getVertexNum() - 1)) {
            auto edge = m_mimHeap.pop(); // edge 的两个端点比有一个 m_marked[i] 为true
            if (m_marked[edge.getEdgeStart()] && m_marked[edge.getEdgeEnd()]) {
                continue;
            }

            m_mstEdges.emplace_back(edge);
            m_mstWeight += edge.getEdgeWeight(); // Weight 支持 +=

            if (!m_marked[edge.getEdgeStart()]) {
                visit(edge.getEdgeStart());
            } else {
                visit(edge.getEdgeEnd());
            }
        }
    }

    void visit(int v) {
        if (m_marked[v]) {
            return;
        }

        m_marked[v] = true;
        typename Graph::iterator it(m_graph, v);
        for (auto edge = it.begin(); !it.end(); edge = it.next()) {
            int otherVertex = edge->getAnotherVertex(v);
            if (!m_marked[otherVertex]) {
                m_mimHeap.push(*edge); // 所有的横切边都入堆
            }
        }
    }

private:
    Graph& m_graph;
    HEAP::Heap<WEIGHTED_GRAPH::Edge<Weight>, CmpGreater<WEIGHTED_GRAPH::Edge<Weight>>> m_mimHeap; // 可换成有限队列
    bool *m_marked; // 切分
    std::vector<WEIGHTED_GRAPH::Edge<Weight>> m_mstEdges{}; // 最小生成树的所有边
    Weight m_mstWeight{}; // 最小生成树的所有边权值和
};

}



#endif