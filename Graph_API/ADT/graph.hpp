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
    std::stringstream WalkThrough(V startNode,WalkMethod method){
        if (!isVertex(startNode))
            throw std::out_of_range("The start node is not in the graph");
        if (method == WalkMethod::DFS)
            return DFS(startNode);
        return BFS(startNode);
    }
    W calcDistace(V startNode,V endNode){
        if (!isVertex(startNode) || !isVertex(endNode))
            throw std::out_of_range("The start or end node is not in the graph");
        if (startNode == endNode)
            return W();
        size_t vertexSize = vertexCount();
        Vector<W> distance(vertexSize,std::numeric_limits<W>::max());
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
                    heap.insert(std::make_pair(distance[nextLocation],it->data.orient));
                }
            }
        }
        return distance[alias[endNode]];
    }
    std::stringstream getLongestPath(V startNode){
        if (!isVertex(startNode))
            throw std::out_of_range("The start node is not in the graph");
        std::stringstream res;
        size_t vertexSize = vertexCount();
        Vector<W> distance(vertexSize,-std::numeric_limits<W>::max());
        distance[alias[startNode]] = 0;
        Heap<std::pair<W,V>> heap;
        heap.insert(std::make_pair(0,startNode));
        Vector<V> parent(vertexSize,-1);
        while (!heap.isEmpty()){
            V current = heap.findMin().second;
            heap.deleteMin();
            size_t currentLocation = locateMap[alias[current]];
            for (typename AdjList::iterator it = graph[currentLocation].begin(); it != graph[currentLocation].end(); it++){
                V temp = current;
                std::cout<<current<<"->"<<it->data.orient<<std::endl;
                size_t nextLocation = locateMap[alias[it->data.orient]];
                W weight = it->data.weight;
                if (distance[nextLocation] <= distance[currentLocation] + weight){
                    distance[nextLocation] = distance[currentLocation] + weight;
                    std::cout<<current<<"->"<<it->data.orient<<'('<<nextLocation<<')'<<" - "<<distance[nextLocation]<<std::endl;
                    heap.insert(std::make_pair(-distance[nextLocation],it->data.orient));
                    parent[nextLocation] = current;
                }
            }
        }
        size_t maxLocation = 0;
        for (size_t i = 1; i < vertexSize; i++){
            std::cout<<graph[i].vertex<<":"<< distance[maxLocation]<<std::endl;
            if (distance[i] < distance[maxLocation] && distance[i] > -std::numeric_limits<W>::max())
                maxLocation = i;
        }
        while (maxLocation != 0){
            res << graph[maxLocation].vertex << "->";
            maxLocation = locateMap[alias[parent[maxLocation]]];
        }
        res << "end";
        return res;
    }
};
}
#include "graph.tpp"
#endif /* graph_hpp */
