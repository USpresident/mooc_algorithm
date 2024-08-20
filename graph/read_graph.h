#ifndef READ_GRAPH_H
#define READ_GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>

#include "../common/common.h"

namespace GRAPH {

template<typename Graph>
class ReadGraph : public NoCopyAble {
public:
    // graph是外部传入的，外部根据文件中的数据设置节点个数
    ReadGraph(const std::string& filename, Graph& graph) {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            std::cout << "Error: open file fail." << std::endl;
            return;
        }

        std::string line;
        if (!std::getline(inputFile, line)) {
            return;
        }
        std::stringstream ss(line);
        int vNum, eNum;
        ss >> vNum >> eNum;
        
        assert(graph.getVertexNum() == vNum);

        for (int i = 0; i < eNum; ++i) {
            if (!std::getline(inputFile, line)) {
                return;
            }
            std::stringstream ss(line);
            int u, v;
            ss >> u >> v;
            assert((u >= 0) && (u < vNum));
            assert((v >= 0) && (v < vNum));
            graph.addEdge(u, v);
        }

        inputFile.close();
    }

};

}


#endif