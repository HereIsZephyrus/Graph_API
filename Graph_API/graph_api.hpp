//
//  graph_api.hpp
//  Graph_API
//
//  Created by ChanningTong on 12/29/24.
//

#ifndef graph_api_hpp
#define graph_api_hpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <cstring>
#include <string>
#include "./ADT/graph.hpp"
namespace WUSG{
using namespace tcb;
void CreateGraphFromFile(const std::string& filename, WUSGraph<std::string, double>& graph);
int MaxDegree(const WUSGraph<std::string, double>& graph);
//void Print(const WUSGraph<std::string, double>& graph, std::ostream& os){os<<graph;}
template <typename Func>
void DFS(const WUSGraph<std::string, double>& graph, const std::string& startNode, Func func){
    graph.WalkThrough(startNode, WalkMethod::DFS, func);
}
template <typename Func, typename... Args>
void BFS(const WUSGraph<std::string, double>& graph, const std::string& startNode, Func func, Args... args){
    graph.WalkThrough(startNode, WalkMethod::BFS, func, args...);
}
}
#endif /* graph_api_hpp */
