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
#include <set>
namespace WUSG{
using std::string;
void CreateGraphFromFile(const std::string& filename, WUSGraph<std::string, double>& graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file");
    }
    std::string line;
    int numVertices, numEdges;
    std::getline(file, line);
    std::istringstream(line) >> numVertices;
    std::getline(file, line);
    std::istringstream(line) >> numEdges;
    for (int i = 0; i < numVertices; ++i) {
        std::getline(file, line);
        graph.addVertex(line);
    }
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
int MaxDegree(const WUSGraph<std::string, double>& graph){
    std::set<string> vertices = graph.getVertice();
    int maxDegree = 0;
    for (std::set<string>::const_iterator vertex = vertices.begin(); vertex != vertices.end(); vertex++){
        int degree = graph.getDegree(*vertex);
        if (degree > maxDegree)
            maxDegree = degree;
        }
    return maxDegree;
}
double Steiner(const WUSGraph<std::string, double>& graph,const Vector<std::string>& keyVertices){
    return graph.steinerTree(keyVertices);
}
Vector<std::pair<std::string,std::string>> Prim(WUSGraph<std::string, double>& graph){
    return graph.calcMST();
}
void Print(const WUSGraph<std::string, double>& graph,ostream& os){
    os<<graph;
}
}
