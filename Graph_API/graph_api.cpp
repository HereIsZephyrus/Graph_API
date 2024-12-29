//
//  graph_api.cpp
//  Graph_API
//
//  Created by ChanningTong on 12/29/24.
//

#include "graph_api.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
namespace WUSG{
void CreateGraphFromFile(const std::string& filename, WUSGraph<std::string, double>& graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file");
    }
    
    std::string line;
    int numVertices, numEdges;
    
    // Read number of vertices
    std::getline(file, line);
    std::istringstream(line) >> numVertices;
    
    // Read number of edges
    std::getline(file, line);
    std::istringstream(line) >> numEdges;
    
    // Read vertices
    for (int i = 0; i < numVertices; ++i) {
        std::getline(file, line);
        graph.addVertex(line);
    }
    
    // Read edges
    for (int i = 0; i < numEdges; ++i) {
        std::getline(file, line);
        std::istringstream iss(line);
        std::string vertex1, vertex2;
        double weight;
        iss >> vertex1 >> vertex2 >> weight;
        graph.addEdge(vertex1, vertex2, weight);
    }
    
    file.close();
}
}
