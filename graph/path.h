#ifndef PATH_H
#define PATH_H

#include <stack>
#include <vector>
#include <queue>

#include "../common/common.h"

namespace GraphAlgorithm {

// 图的深度优先遍历
template <typename Graph>
class Path : public NoCopyAble {
public:
    Path(Graph& graph, int source) : m_graph(graph)
    {
        if ((source < 0) || (source >= m_graph.getVertexNum())) {
            return;
        }

        m_isVisited = new bool[graph.getVertexNum()];
        m_from = new int[graph.getVertexNum()];
        m_source = source;
        for (int i = 0; i < graph.getVertexNum(); ++i) {
            m_isVisited[i] = false;
            m_from[i] = -1;
        }

        calcPath(); // 深度优先遍历 
    }

    ~Path()
    {
        delete[] m_isVisited;
        delete[] m_from;
    }

    bool hasPathTo(int w)
    {
        if ((w < 0) || (w >= m_graph.getVertexNum())) {
            return false;
        }

        return m_isVisited[w];
    }

    void showPathTo(int w)
    {
        std::vector<int> path = pathTo(w);
        std::cout << "Path from " << m_source << " to " << w << " is: ";
        if (path.empty()) {
            std::cout << "Null..." << std::endl;
            return;
        }

        for (int i = 0; i < path.size(); i++) {
            std::cout << path[i];
            if ( i == path.size() - 1) {
                std::cout << std::endl;
            } else{
                std::cout << " -> ";
            }
        }
    }

private:

    void calcPath()
    {
        dfs(m_source);
    }

    void dfs(int i)
    {
        m_isVisited[i] = true;
        typename Graph::iterator it(m_graph, i);
        for (int w = it.begin(); !it.end(); w = it.next()) {
            if (!m_isVisited[w]) {
                m_from[w] = i;
                dfs(w);
            }
        }
    }

    std::vector<int> pathTo(int w)
    {
        std::vector<int> path{};
        if (!hasPathTo(w)) {
            return path;
        }

        std::stack<int> st{};
        for (int i = w; i != m_source; i = m_from[i]) {
            st.push(i);
        }
        st.push(m_source);

        while (!st.empty()) {
            path.emplace_back(st.top());
            st.pop();
        }

        return path;
    }

private:
    Graph& m_graph;
    bool *m_isVisited;
    int *m_from; // 深度优先使用
    int m_source;
};

// 图的广度优先遍历
template<typename Graph>
class ShortestPath : public NoCopyAble {
public:
    ShortestPath(Graph& graph, int source) : m_graph(graph)
    {
        if ((source < 0) || (source >= m_graph.getVertexNum())) {
            return;
        }

        m_isVisited = new bool[graph.getVertexNum()];
        m_from = new int[graph.getVertexNum()];
        m_distance = new int[graph.getVertexNum()];
        m_source = source;
        for (int i = 0; i < graph.getVertexNum(); ++i) {
            m_isVisited[i] = false;
            m_from[i] = -1;
            m_distance[i] = -1;
        }

        calsShortestPath(); // 广度优先遍历 
    }

    ~ShortestPath()
    {
        delete[] m_isVisited;
        delete[] m_from;
        delete[] m_distance;
    }

    /**
     * @brief 指定的源节点到节点w是否存在路径
     */
    bool hasPathTo(int w) const
    {
        if ((w < 0) || (w >= m_graph.getVertexNum())) {
            return false;
        }

        return m_isVisited[w];
    }

    void showPathTo(int w)
    {
        std::vector<int> path = pathTo(w);
        std::cout << "Path from " << m_source << " to " << w << " is: ";
        if (path.empty()) {
            std::cout << "Null..." << std::endl;
            return;
        }

        for (int i = 0; i < path.size(); i++) {
            std::cout << path[i];
            if ( i != path.size() - 1) {
                std::cout << " -> ";
            }
        }

        std::cout << ", shorstest distance: " << m_distance[w] << std::endl;
    }

private:
    void calsShortestPath()
    {
        std::queue<int> q{};
        q.push(m_source);
        m_distance[m_source] = 0;
        m_isVisited[m_source] = true;

        while (!q.empty()) {
            int i = q.front();
            q.pop();
            typename Graph::iterator it(m_graph, i);
            for (int w = it.begin(); !it.end(); w = it.next()) {
                if (m_isVisited[w]) {
                    continue;
                }

                q.push(w);
                m_isVisited[w] = true;
                m_from[w] = i;
                m_distance[w] = m_distance[i] + 1; // 距离为当前节点到源节点的距离加1
            }
        }
    }

    std::vector<int> pathTo(int w)
    {
        std::vector<int> path{};
        if (!hasPathTo(w)) {
            return path;
        }

        std::stack<int> st{};
        for (int i = w; i != m_source; i = m_from[i]) {
            st.push(i);
        }
        st.push(m_source);

        while (!st.empty()) {
            path.emplace_back(st.top());
            st.pop();
        }

        return path;
    }

private:
    Graph& m_graph;
    bool *m_isVisited;
    int *m_from;
    int *m_distance; // source到每个节点的最短距离
    int m_source;
};

}

#endif