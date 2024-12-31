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
    Neighbor getNeighbor(V checkNode) const;
    const Vector<EdgeInfo>& getMST();
    W getMSTWeight() {return MST.getTotalWeight();}
    template <typename Func, typename ...Args>
    void WalkThrough(V startNode,WalkMethod method,Func func,Args... args);
    W calcDistace(V startNode,V endNode);
    std::stringstream getLongestPath(V startNode);
    W steinerTree(const Vector<V>& keyVertices) const;
    int countConnectedComponents(){
        Vector<bool> visited(vertexCount(),false);
        int count = 0;
        auto visit = [this](V vertex,Vector<bool>* visited){
            (*visited)[locateMap[alias[vertex]]] = true;
        };
        for (size_t i = 0; i < graph.getSize(); i++){
            if (!visited[i]){
                DFS(graph[i].vertex,visit,&visited);
                count++;
            }
        }
        return count;
    }
    Vector<std::pair<V,V>> calcMST(){
        V startNode = graph[0].vertex;
        return calcMST(startNode);
    }
    Vector<std::pair<V,V>> calcMST(V startNode){
        if (!isVertex(startNode))
            throw std::out_of_range("The start or end node is not in the graph");
        size_t vertexSize = vertexCount();
        Vector<W> distance(vertexSize,std::numeric_limits<W>::max());
        Vector<int> parent(vertexSize,-1);
        Dijkstra(startNode,distance,parent);
        Vector<std::pair<V,V>> res;
        std::queue<V> q;
        Vector<bool> visited(vertexSize,false);
        size_t startLocation = locateMap[alias[startNode]];
        Queue<size_t> queue;
        queue.enqueue(startLocation);
        visited[startLocation] = true;
        while (!queue.isEmpty()){
            size_t currentLocation = queue.front();
            if (parent[currentLocation] != -1){
                size_t parentLoc = locateMap[parent[currentLocation]];
                std::pair<V,V> vertex = std::make_pair(graph[parent[parentLoc]].vertex, graph[currentLocation].vertex);
                res.push_back(vertex);
            }
            queue.dequeue();
            for (typename AdjList::iterator it = graph[currentLocation].begin(); it != graph[currentLocation].end(); it++){
                size_t nextLocation = locateMap[alias[it->data.orient]];
                if (!visited[nextLocation]){
                    queue.enqueue(nextLocation);
                    visited[nextLocation] = true;
                }
            }
        }
        return res;
    }
    void Dijkstra(V startNode,Vector<W>& distance,Vector<int>& parent){
        distance[alias[startNode]] = 0;
        Heap<std::pair<W,V>> heap;
        heap.insert(std::make_pair(0,startNode));
        while (!heap.isEmpty()){
            V current = heap.findMin().second;
            heap.deleteMin();
            size_t currentLocation = locateMap[alias[current]];
            for (typename AdjList::iterator it = graph[currentLocation].begin(); it != graph[currentLocation].end(); it++){
                size_t nextLocation = locateMap[alias[it->data.orient]];
                W weight = it->data.weight;
                if (distance[nextLocation] > distance[currentLocation] + weight){
                    distance[nextLocation] = distance[currentLocation] + weight;
                    parent[nextLocation] = alias[current];
                    heap.insert(std::make_pair(distance[nextLocation],it->data.orient));
                }
            }
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const WUSGraph<V, W>& graph) {
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
