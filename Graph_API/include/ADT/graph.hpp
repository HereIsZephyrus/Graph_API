//
//  graph.hpp
//  Graph_API
//
//  Created by ChanningTong on 12/28/24.
//

#ifndef graph_hpp
#define graph_hpp

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <memory>
#include <map>
#include <stdexcept>
#include <sstream>
#include <cmath>
#include "hash.hpp"
#include "disjsets.hpp"
#include "heap.hpp"
#include "tree.hpp"
using std::string;
namespace tcb {
enum class WalkMethod : bool{
    DFS,
    BFS
};
template <typename V, typename W>
struct EdgeInfo{
    VertexPair vertex;
    W weight;
    bool operator==(const EdgeInfo& rhs) const {
        return (vertex == rhs.vertex) && (weight == rhs.weight);
    }
    bool operator<(const EdgeInfo& rhs) const {
        if (weight == rhs.weight)
            return vertex < rhs.vertex;
        return weight < rhs.weight;
    }
    bool operator>(const EdgeInfo& rhs) const {
        if (weight == rhs.weight)
            return vertex > rhs.vertex;
        return weight > rhs.weight;
    }
    EdgeInfo() : vertex(VertexPair()), weight(W()) {}
    EdgeInfo(VertexPair v, W w) : vertex(v), weight(w) {}
};
template <typename V = string, typename W = double>
class WUSGraph{
public:
    using Neighbor = Vector<std::pair<V,W>>;
    using EdgeInfo = EdgeInfo<V, W>;
    struct Edge;
    struct Message;
    class AdjList;
    class EdgeTable;
    class MinSpanForest;
private:
    using Node = typename List<Edge>::Node;
    using pEdge = Node*;
    EdgeTable edgeTable;
    HashMap<V, int> alias;
    HashMap<int, size_t> locateMap;
    Vector<AdjList> graph;
    int vertexCounter;
    MinSpanForest MST;
    void remove(size_t location,EdgeTable& edgeTable);
    template <typename Func>
    void DFS(V startNode,Func visit);
    template <typename Func>
    void DFSUtil(size_t startLocation,Vector<bool>& visited,Func visit);
    template <typename Func>
    void BFS(V startNode,Func visit);
public:
    explicit WUSGraph(int v): vertexCounter(0),MST(*this){graph.reserve(v);}
    //required
    size_t vertexCount() const {return graph.getSize();}
    size_t edgeCount() const {return edgeTable.getSize();}
    const std::set<V>& getVertice() const{return alias.getKeySet();}
    bool isVertex(V checkVertex) const {return alias.containKey(checkVertex);}
    const std::set<VertexPair>& getVertexpairs(){return edgeTable.getKeySet();}
    void addVertex(V newVertex);
    void removeVertex(V delVertex);
    int getDegree(V checkVertex) const;
    int getDegree(size_t location) const {return static_cast<int>(graph[location].getSize());}
    void addEdge(V v1,V v2,W weight);
    void removeEdge(V v1,V v2);
    bool hasEdge(V v1,V v2) const;
    W getWeight(V v1,V v2) const;
    V getVertex(V temp) const;
    V getStartVertex() const {return graph[0].vertex;};
    Neighbor getNeighbor(V checkNode) const;
    const Vector<EdgeInfo>& getMST();
    W getMSTWeight() {return MST.getTotalWeight();}
    template <typename Func>
    void WalkThrough(V startNode,WalkMethod method,Func func);
    W calcDistace(V startNode,V endNode);
    W calcDistace(V startNode,V endNode,Vector<std::pair<V,V>>& vertices);
    std::stringstream getLongestPath(V startNode);
    W steinerTree(const Vector<V>& keyVertices);
    int countConnectedComponents();
    W calcMST(V startNode,Vector<std::pair<V,V>>& vertices);
    void Dijkstra(V startNode,Vector<W>& distance,Vector<int>& parent);
    friend std::ostream& operator<<(std::ostream& os, const WUSGraph<V, W>& graph){
        os << "Vertices: " << graph.vertexCount() << "\n";
        os << "Edges: " << graph.edgeCount() << "\n";
        for (const auto& vertex : graph.getVertice()) {
            os << vertex << " -> ";
            auto neighbors = graph.getNeighbor(vertex);
            for (const auto& neighbor : neighbors) {
                os << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            os << "\n";
        }
        return os;
    }
};
}
#include "graph.tpp"
#endif /* graph_hpp */
