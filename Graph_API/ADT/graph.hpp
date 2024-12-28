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
#include "hash.hpp"
using std::string;
namespace tcb {
template <typename V = string, typename W = double>
class WUSGraph{
    using Vertex = int;
    struct Edge{
        Vertex orient;
        W weight;
        std::shared_ptr<Edge> friendEdge;
        Edge(Vertex to,W w):orient(to),weight(w),friendEdge(nullptr){}
    };
    struct AdjList{
        List<Edge> edges;
        Vertex vertexID;
        void remove(){}
        AdjList(Vertex ID = 0):vertexID(ID){}
    };
    HashMap<V, Vertex> alias;
    HashMap<Vertex, size_t> locateMap;
    Vector<AdjList> graph;
    int vertexSize,edgeNum;
    Vertex vertexCounter;
    size_t vertexNum;
public:
    explicit WUSGraph(int v): vertexSize(v),edgeNum(0),vertexNum(0),vertexCounter(0){
        graph.reserve(v);
    }
    int vertexCount() const {return vertexSize;}
    int edgeCount() const {return edgeNum;}
    void addVertex(V newVertex){
        if (alias.containKey(newVertex))
            return;
        alias.insert(newVertex,vertexCounter);
        graph.push_back(AdjList(vertexCounter));
        locateMap.insert(vertexCounter, vertexNum);
        ++vertexCounter;
        ++vertexNum;
    }
    void removeVertex(V delVertex){
        if (!alias.containKey(delVertex))
            return;
        alias.remove(delVertex);
        size_t location = locateMap[delVertex];
        Vertex backVertexID = graph.back().vertexID;
        graph[location].remove();
        graph[location] = graph.back();
        locateMap[backVertexID] = location;
    }
    bool isVertex(V checkVertex) const {return alias.containKey(checkVertex);}
    int getDegree(V checkVertex) const {
        if (!alias.containKey(checkVertex))
            return -1;
        size_t location = locateMap[alias[checkVertex]];
        return graph[location].edges.size();
    }
    void addEdge(V v1,V v2,W weight){
        if (!alias.containKey(v1) || !alias.containKey(v2))
            return;
        Vertex id1 = alias[v1], id2 = alias[v2];
        size_t location1 = locateMap[id1],location2 = locateMap[id2];
        std::shared_ptr<Edge> edge1 = std::make_shared<Edge>(id2,weight),edge2 = std::make_shared<Edge>(id1,weight);
        edge1->frendEdge = edge2;   edge2->frendEdge = edge1;
        graph[location1].insert(edge1);    graph[location2].insert(edge2);
    }
    void removeEdge(V v1,V v2){
        if (!alias.containKey(v1) || !alias.containKey(v2))
            return;
        Vertex id1 = alias[v1], id2 = alias[v2];
        size_t location1 = locateMap[id1],location2 = locateMap[id2];
        graph[location1].removeNode(id2);    graph[location2].removeNode(id1);
    }
    bool hasEdge(V v1,V v2){
        if (!alias.containKey(v1) || !alias.containKey(v2))
            return false;
        AdjList& list = graph[locateMap[alias[v1]]];
        return (list.searchNode(v2) != list.end());
    }
    W getWeight(V v1,V v2){
        if (!alias.containKey(v1) || !alias.containKey(v2))
            return W();
        W weight = W();
        AdjList& list = graph[locateMap[alias[v1]]];
        typename List<Edge>::iterator loc = list.searchNode(v2);
        if (loc != list.end())
            return loc.weight;
        return W();
    }
};
}
#endif /* graph_hpp */
