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
#include "hash.hpp"
using std::string;
namespace tcb {
template <typename V = string, typename W = double>
class WUSGraph{
    class AdjList;
    struct Edge;
    using Node = typename List<Edge>::Node;
    using pEdge = Node*;
    using pList = AdjList*;
    struct Edge{
        int orient;
        W weight;
        pEdge friendEdge;
        pList friendBucket;
        Edge(int to = 0,W w = W(),pList friendList = nullptr):orient(to),weight(w),friendEdge(nullptr),friendBucket(friendList){}
        bool operator==(const Edge& other) const {
            return orient == other.orient && weight == other.weight;
        }
        ~Edge(){
            if (friendEdge != nullptr){
                friendEdge->prev->next = friendEdge->next;
                friendEdge->next->prev = friendEdge->prev;
                delete friendEdge;
                --friendBucket->size;
            }
        }
    };
    class EdgeTable : public HashMap<VertexPair, pEdge>{
    public:
        void removeNode(VertexPair vertices){
            pEdge orientEdge = this->getRefValue(vertices);
            orientEdge->prev->next = orientEdge->next;
            orientEdge->next->prev = orientEdge->prev;
            delete orientEdge;
        }
    };
    EdgeTable edgeTable;
    class AdjList : public List<Edge>{
        friend Edge;
    public:
        using Node = typename List<Edge>::Node;
        using iterator = typename List<Edge>::iterator;
        using const_iterator = typename List<Edge>::const_iterator;
        int vertexID;
        void insert(pEdge edge){
            Node *p = this->end()._ptr();
            edge->prev = p->prev;
            edge->next = p;
            this->size++;
            p->prev = p->prev->next = edge;
        }
        void pop() {--this->size;}
        void remove(){this->clear();}
        AdjList(int ID = -1):vertexID(ID){}
    };
    HashMap<V, int> alias;
    HashMap<int, size_t> locateMap;
    Vector<AdjList> graph;
    int vertexSize,edgeNum;
    int vertexCounter;
    size_t vertexNum;
public:
    explicit WUSGraph(int v): vertexSize(v),edgeNum(0),vertexNum(0),vertexCounter(0){
       graph.reserve(v);
    }
    int vertexCount() const {return vertexCounter;}
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
        size_t location = locateMap[alias[delVertex]];
        int backVertexID = graph.back().vertexID;
        graph[location].remove();
        graph[location] = graph.back();
        locateMap[backVertexID] = location;
        --vertexNum;
    }
    bool isVertex(V checkVertex) const {return alias.containKey(checkVertex);}
    int getDegree(V checkVertex) const {
        if (!alias.containKey(checkVertex))
            return -1;
        size_t location = locateMap[alias[checkVertex]];
        return static_cast<int>(graph[location].getSize());
    }
    void addEdge(V v1,V v2,W weight){
        if (!alias.containKey(v1) || !alias.containKey(v2))
            return;
        int id1 = alias[v1], id2 = alias[v2];
        size_t location1 = locateMap[id1],location2 = locateMap[id2];
        pEdge edge1 = new Node(Edge(id2,weight,&graph[id1]));
        pEdge edge2 = new Node(Edge(id1,weight,&graph[id2]));
        edge1->data.friendEdge = edge2;   edge2->data.friendEdge = edge1;
        graph[location1].insert(edge1);    graph[location2].insert(edge2);
        VertexPair vertices = std::make_pair(graph[location1].vertexID,graph[location2].vertexID);
        edgeTable.insert(vertices, edge1); //has linked preview and next(I gusses
    }
    void removeEdge(V v1,V v2){
        if (!alias.containKey(v1) || !alias.containKey(v2))
            return;
        int id1 = alias[v1], id2 = alias[v2];
        size_t location1 = locateMap[id1],location2 = locateMap[id2];
        VertexPair vertices = std::make_pair(id1,id2);
        bool oneway = edgeTable.containKey(vertices);
        if (oneway)
            graph[location1].pop();
        else
            graph[location2].pop();
        edgeTable.removeNode(vertices);
    }
    bool hasEdge(V v1,V v2) const{
        if (!alias.containKey(v1) || !alias.containKey(v2))
            return false;
        int id1 = alias[v1], id2 = alias[v2];
        VertexPair verticesForward = std::make_pair(id1,id2);
        VertexPair verticesBackward = std::make_pair(id2,id1);
        return edgeTable.containKey(verticesForward) || edgeTable.containKey(verticesBackward);
    }
    W getWeight(V v1,V v2) const{
        if (!hasEdge(v1, v2))
            return W();
        int id1 = alias[v1], id2 = alias[v2];
        VertexPair verticesForward = std::make_pair(id1,id2);
        VertexPair verticesBackward = std::make_pair(id2,id1);
        if (edgeTable.containKey(verticesForward))
            return edgeTable[verticesForward]->data.weight;
        if (edgeTable.containKey(verticesBackward))
            return edgeTable[verticesBackward]->data.weight;
        return W();
    }
};
}
#endif /* graph_hpp */
