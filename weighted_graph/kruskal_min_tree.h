#ifndef KRUSKAL_MIM_TREE
#define KRUSKAL_MIM_TREE

#include "../union_find/quick_union_optim2.h"
#include "edge.h"
#include <vector>
#include <queue>
#include <set>

namespace GraphAlgorithm {

template <typename Graph, typename Weight>
class KruskalMST : public NoCopyAble {
public:
    KruskalMST(Graph &graph)
    {
        // 1、对图中所有边按照权值升序排序, 最小堆、优先队列，O(ElogE)

        //    权值一样的边认为是相等的边，std::set会丢边，要用std::multiset
        // std::priority_queue<WEIGHTED_GRAPH::Edge<Weight>,std::vector<WEIGHTED_GRAPH::Edge<Weight>>,
        //     std::greater<WEIGHTED_GRAPH::Edge<Weight>>> edgeSet{};
        std::multiset<WEIGHTED_GRAPH::Edge<Weight>> edgeSet{};
        for (int i = 0; i < graph.getVertexNum(); ++i) {
            typename Graph::iterator it(graph, i);
            for (auto edge = it.begin(); !it.end(); edge = it.next()) {
                // edgeSet.push(*edge);
                edgeSet.insert(*edge);
            }
        }

        UNION_FIND::QuickUnionOptimByRank unionFind(graph.getVertexNum());

        /* 2、依次取出排序后的最小边，如果该边的两个端点不在同一连通分量中，
         *    将该边加入最小生成树中，并将该端点所在连通分量合并
         */

        // while (!edgeSet.empty()) {
        //     const auto &edge = edgeSet.top();
        //     edgeSet.pop();
        for (const auto &edge : edgeSet) {

            // 优化：
            if (m_mstEdges.size() >= graph.getVertexNum() - 1) {
                return;
            }

            // 注意：在 union-find 并查集中，isConnected()函数返回 true 表示成环
            if (unionFind.isConnected(edge.getEdgeStart(), edge.getEdgeEnd())) {
                continue;
            }

            m_mstEdges.emplace_back(edge);
            m_mstWeight += edge.getEdgeWeight();

            unionFind.unionElements(edge.getEdgeStart(), edge.getEdgeEnd());
        }
    }

    ~KruskalMST()
    {
        m_mstEdges.clear();
    }

    void showMST()
    {
        std::cout << "KruskalMST weight: " << m_mstWeight << std::endl;
        for (const auto &edge : m_mstEdges) {
            std::cout << edge << std::endl;
        }
    }

private:
    std::vector<WEIGHTED_GRAPH::Edge<Weight>> m_mstEdges{};
    Weight m_mstWeight{};
};

}

#endif