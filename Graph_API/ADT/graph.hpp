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
    int vertexSize;
    int vertexCounter;
    MinSpanForest MST;
    void remove(size_t location,EdgeTable& edgeTable);
    std::stringstream DFS(V startNode){
        std::stringstream res;
        size_t vertexNum = graph.getSize();
        Vector<bool> visited(vertexNum,false);
        size_t startLocation = locateMap[alias[startNode]];
        DFSUtil(startLocation,visited,res);
        res << "end";
        return res;
    }
    void DFSUtil(size_t startLocation,Vector<bool>& visited,std::stringstream& res){
        visited[startLocation] = true;
        res << graph[startLocation].vertex << "->";
        for (typename AdjList::iterator it = graph[startLocation].begin(); it != graph[startLocation].end(); it++){
            size_t nextLocation = locateMap[alias[it->data.orient]];
            if (!visited[nextLocation])
                DFSUtil(nextLocation,visited,res);
        }
    }
    std::stringstream BFS(V startNode){
        std::stringstream res;
        size_t vertexNum = graph.getSize();
        Vector<bool> visited(vertexNum,false);
        size_t startLocation = locateMap[alias[startNode]];
        Queue<size_t> queue;
        queue.enqueue(startLocation);
        visited[startLocation] = true;
        while (!queue.isEmpty()){
            size_t currentLocation = queue.front();
            queue.dequeue();
            res << graph[currentLocation].vertex << "->";
            for (typename AdjList::iterator it = graph[currentLocation].begin(); it != graph[currentLocation].end(); it++){
                size_t nextLocation = locateMap[alias[it->data.orient]];
                if (!visited[nextLocation]){
                    queue.enqueue(nextLocation);
                    visited[nextLocation] = true;
                }
            }
        }
        res << "end";
        return res;
    }
public:
    explicit WUSGraph(int v): vertexSize(v),vertexCounter(0),MST(*this){graph.reserve(v);}
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
    std::stringstream WalkThrough(V startNode,WalkMethod method){
        if (!isVertex(startNode))
            throw std::out_of_range("The start node is not in the graph");
        if (method == WalkMethod::DFS)
            return DFS(startNode);
        return BFS(startNode);
    }
};
}
#include "graph.tpp"
#endif /* graph_hpp */
