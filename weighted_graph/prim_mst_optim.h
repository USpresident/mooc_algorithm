#ifndef PRIM_MST_OPTIM_H
#define PRIM_MST_OPTIM_H

#include "../heap/index_heap.h"
#include "edge.h"
#include <vector>

namespace GraphAlgorithm {

template <typename Graph, typename Weight>
class PrimMst : public NoCopyAble {
public:
    PrimMst(Graph &graph) : m_graph(graph),
        m_minHeap(HEAP::IndexHeap<Weight, CmpGreater<Weight>>(graph.getVertexNum()))
    {
        m_marked = new bool[graph.getVertexNum()];
        std::fill(m_marked, m_marked + graph.getVertexNum(), false);
        m_weight = 0;
        m_mstEdges.reserve(graph.getVertexNum());
        m_edgeTo.resize(graph.getVertexNum(), nullptr);

        prim();
    }

    ~PrimMst() {
        delete[] m_marked;
    }

    const std::vector<WEIGHTED_GRAPH::Edge<Weight>> &getMstEdges() const {
        return m_mstEdges;
    }

    const Weight &getMstWeight() const {
        return m_weight;
    }

    void showMST()
    {
        std::cout << "PrimeMST weight: " << m_weight << std::endl;
        for (const auto &edge : m_mstEdges) {
            std::cout << edge << std::endl;
        }
    }

private:
    void prim() {
        visit(0);

        while (!m_minHeap.isEmpty()) {
            int v = m_minHeap.popTopElemIndex();
            if (m_edgeTo[v] == nullptr) {
                return;
            }

            m_mstEdges.push_back(*m_edgeTo[v]);
            m_weight += m_edgeTo[v]->getEdgeWeight();
            visit(v);
        }
    }

    void visit(int v) {
        if (m_marked[v]) {
            return;
        }

        m_marked[v] = true;

        typename Graph::iterator it(m_graph, v);
        for (auto *edge = it.begin(); !it.end(); edge = it.next()) {
            int w = edge->getAnotherVertex(v);
            if (m_marked[w]) {
                continue;
            }

            if (m_edgeTo[w] == nullptr) {
                m_edgeTo[w] = edge;
                m_minHeap.push(w, edge->getEdgeWeight());
            } else if (edge->getEdgeWeight() < m_edgeTo[w]->getEdgeWeight()) {
                m_edgeTo[w] = edge;
                m_minHeap.change(w, edge->getEdgeWeight());
            }
        }
    }

private:
    Graph &m_graph;
    // HEAP::IndexHeap<WEIGHTED_GRAPH::Edge<Weight>, CmpGreater<WEIGHTED_GRAPH::Edge<Weight>>> m_minHeap;
    HEAP::IndexHeap<Weight, CmpGreater<Weight>> m_minHeap; // 保存权值即可，不是所有的横切边都入堆
    std::vector<WEIGHTED_GRAPH::Edge<Weight> *> m_edgeTo; // 每个节点先连的最小边
    bool *m_marked;
    std::vector<WEIGHTED_GRAPH::Edge<Weight>> m_mstEdges;
    Weight m_weight;
};
}

#endif