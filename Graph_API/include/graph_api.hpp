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
#include "graph.hpp"
namespace WUSG{
using namespace tcb;
using namespace base;
using std::string;
template <typename W>
using Graph = WUSGraph<Vertex<W>, W>;
template <typename V, typename W>
void CreateGraphFromFile(const string& filename, WUSGraph<V,W>& graph,bool BatchRead);
template <typename V, typename W>
int MaxDegree(const WUSGraph<V,W>& graph);
template <typename V, typename W>
double Sparseness(const WUSGraph<V,W>& graph);
template <typename V, typename W>
int CalcConnectCompoent(const WUSGraph<V,W>& graph);
template <typename V, typename W, typename Func>
void DFS(WUSGraph<V,W>& graph, const V& startNode, Func func);
template <typename V, typename W, typename Func>
void BFS(WUSGraph<V,W>& graph, const V& startNode, Func func);
template <typename V, typename W>
double Steiner(WUSGraph<V,W>& graph,const Vector<V>& keyVertices);
template <typename V, typename W>
W Prim(WUSGraph<V,W>& graph,Vector<std::pair<V,V>>& vertices,V startNode);
template <typename V, typename W>
W ShortestPath(WUSGraph<V,W>& graph,V startNode,V termNode,Vector<std::pair<V,V>>& vertices);
template <typename V, typename W>
std::string GetNeighbor(const WUSGraph<V,W>& graph,V node);
template <typename V, typename W>
void Print(const WUSGraph<V,W>& graph,ostream& os);
}
#include "graph_api.inl"
#endif /* graph_api_hpp */
