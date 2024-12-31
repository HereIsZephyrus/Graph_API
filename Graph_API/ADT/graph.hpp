//
//  graph.hpp
//  Graph_API
//
//  Created by ChanningTong on 12/28/24.
//

#ifndef graph_hpp
#define graph_hpp

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
    using Neighbor = Vector<std::pair<V,W>>;
    using EdgeInfo = EdgeInfo<V, W>;
    struct Edge;
    struct Message;
    class AdjList;
    class EdgeTable;
    class MinSpanForest;
    using Node = typename List<Edge>::Node;
    using pEdge = Node*;
    EdgeTable edgeTable;
    HashMap<V, int> alias;
    HashMap<int, size_t> locateMap;
    Vector<AdjList> graph;
    int vertexCounter;
    MinSpanForest MST;
    void remove(size_t location,EdgeTable& edgeTable);
    template <typename Func, typename ...Args>
    void DFS(V startNode,Func visit,Args... args);
    template <typename Func, typename ...Args>
    void DFSUtil(size_t startLocation,Vector<bool>& visited,Func visit,Args... args);
    template <typename Func, typename ...Args>
    void BFS(V startNode,Func visit,Args... args);
public:
    explicit WUSGraph(int v): vertexCounter(0),MST(*this){graph.reserve(v);}
    //required
    size_t vertexCount() const {return graph.getSize();}
    size_t edgeCount() const {return edgeTable.getSize();}
    const std::set<V>& getVertice() const{return alias.getKeySet();}
    bool isVertex(V checkVertex) const {return alias.containKey(checkVertex);}
    void addVertex(V newVertex);
    void removeVertex(V delVertex);
    int getDegree(V checkVertex) const;
    void addEdge(V v1,V v2,W weight);
    void removeEdge(V v1,V v2);
    bool hasEdge(V v1,V v2) const;
    W getWeight(V v1,V v2) const;
    Neighbor getNeighbor(V checkNode);
    const Vector<EdgeInfo>& getMST();
    W getMSTWeight() {return MST.getTotalWeight();}
    template <typename Func, typename ...Args>
    void WalkThrough(V startNode,WalkMethod method,Func func,Args... args);
    W calcDistace(V startNode,V endNode);
    std::stringstream getLongestPath(V startNode);
    W steinerTree(const Vector<V>& keyVertices);
};
}
#include "graph.tpp"
#endif /* graph_hpp */
