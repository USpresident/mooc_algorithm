#ifndef EDGE_H

#define EDGE_H

#include <iostream>

namespace WEIGHTED_GRAPH {

template <typename Weight>
class Edge {
public:
    Edge(int start, int end, const Weight weight)
    {
        m_vStart = start;
        m_vEnd = end;
        m_weight = weight;
    }

    Edge() {}
    ~Edge() {}

    int getEdgeStart() const
    {
        return m_vStart;
    }

    int getEdgeEnd() const
    {
        return m_vEnd;
    }

    Weight getEdgeWeight() const
    {
        return m_weight;
    }

    /**
     * @brief 指定边的一个端点，求另一端
     */
    int getAnotherVertex(int v) const
    {
        if ((v != m_vStart) && (v != m_vEnd)) {
            return -1;
        }

        return (v == m_vStart)? m_vEnd : m_vStart;
    }

    bool operator < (const Edge &edge) const
    {
        return (m_weight < edge.m_weight);
    }

    bool operator <= (const Edge &edge) const
    {
        return (m_weight <= edge.m_weight);
    }

    bool operator > (const Edge &edge) const
    {
        return (m_weight > edge.m_weight);
    }

    bool operator >= (const Edge &edge) const
    {
        return (m_weight >= edge.m_weight);
    }

    bool operator == (const Edge &edge) const
    {
        return (m_weight < edge.m_weight);
    }

    friend std::ostream &operator<<(ostream &os, const Edge &edge)
    {
        os << "(" << edge.m_vStart << " - " << edge.m_vEnd << ", weight:" << edge.m_weight << ")";
        return os;
    }

private:
    int m_vStart; // 有向图时，从 m_vStart -> m_vEnd
    int m_vEnd;
    Weight m_weight;
};
}

#endif