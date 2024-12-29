//
//  graph_api.hpp
//  Graph_API
//
//  Created by ChanningTong on 12/29/24.
//

#ifndef graph_api_hpp
#define graph_api_hpp
#include <cstring>
#include <string>
#include "./ADT/graph.hpp"
namespace WUSG{
using namespace tcb;
void CreateGraphFromFile(const std::string& filename, WUSGraph<std::string, double>& graph);
void MaxDegree(const WUSGraph<std::string, double>& graph);
void DFS();
void BFS();
}
#endif /* graph_api_hpp */
