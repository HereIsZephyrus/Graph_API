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
    };
    class EdgeTable : public HashMap<VertexPair, pEdge>{
    public:
        pEdge removeNode(VertexPair vertices,size_t& currentSize){
            using Bucket = HashMap<VertexPair, pEdge>::Bucket;
            //I can't use the getRef below, is it return a copy of the pointer? why?
            //pEdge orientEdge = this->getRefValue(vertices);
            //that's why delete orientEdge will not raise a double release!
            const Bucket& orientList = this->hashList[this->hash(vertices)];
            typename Bucket::iterator itr = orientList.begin();
            for (; itr != orientList.end(); itr++){
                if ((*itr).first == vertices)
                    break;
            }
            pEdge ret_p = (*itr).second->next;
            (*itr).second->next->prev->next = (*itr).second->next->next;
            (*itr).second->next->next->prev = (*itr).second->next->prev;
            pEdge friendEdge = (*itr).second->next->data.friendEdge;
            pList friendBucket = (*itr).second->next->data.friendBucket;
            if (friendEdge != nullptr){
                friendEdge->prev->next = friendEdge->next;
                friendEdge->next->prev = friendEdge->prev;
                delete friendEdge;
            }
            delete (*itr).second->next; //why this will not double release?
            this->remove(vertices);
            --friendBucket->size;
            --currentSize;
            friendBucket = nullptr;
            return ret_p;
        }
    };
    EdgeTable edgeTable;
    class AdjList : public List<Edge>{
        friend EdgeTable;
    public:
        using Node = typename List<Edge>::Node;
        using iterator = typename List<Edge>::iterator;
        using const_iterator = typename List<Edge>::const_iterator;
        int vertexID;
        void insert(pEdge edge){
            Node *p = this->begin()._ptr();
            edge->prev = p->prev;
            edge->next = p;
            this->size++;
            p->prev = p->prev->next = edge;
        }
        void pop() {--this->size;}
        void remove(EdgeTable& edgeTable){
            pEdge it = this->head->next;
            while (!this->isEmpty()){
                VertexPair verticesForward = std::make_pair(vertexID,it->data.orient); //I can't use it->weight since weight is not the member of Node but the menber of data,how to overload?
                VertexPair verticesBackward = std::make_pair(it->data.orient,vertexID);
                if (edgeTable.containKey(verticesForward))
                    it = edgeTable.removeNode(verticesForward,this->size);
                if (edgeTable.containKey(verticesBackward))
                    it = edgeTable.removeNode(verticesBackward,this->size);
            }
        }
        AdjList(int ID = -1):vertexID(ID){}
        size_t& refSize() {return this->size;}
    };
    HashMap<V, int> alias;
    HashMap<int, size_t> locateMap;
    Vector<AdjList> graph;
    int vertexSize;
    int vertexCounter;
    size_t vertexNum;
public:
    explicit WUSGraph(int v): vertexSize(v),vertexNum(0),vertexCounter(0){
       graph.reserve(v);
    }
    size_t vertexCount() const {return vertexNum;}
    size_t edgeCount() const {return edgeTable.getSize();}
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
        size_t location = locateMap[alias[delVertex]];
        alias.remove(delVertex);
        int backVertexID = graph.back().vertexID;
        graph[location].remove(edgeTable);
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
        pEdge edge1 = new Node(Edge(id2,weight,&graph[id2]));
        pEdge edge2 = new Node(Edge(id1,weight,&graph[id1]));
        edge1->data.friendEdge = edge2;   edge2->data.friendEdge = edge1;
        graph[location1].insert(edge1);    graph[location2].insert(edge2);
        VertexPair vertices = std::make_pair(id1,id2);
        edgeTable.insert(vertices, edge1); //has linked preview and next(I gusses
    }
    void removeEdge(V v1,V v2){
        if (!alias.containKey(v1) || !alias.containKey(v2))
            return;
        int id1 = alias[v1], id2 = alias[v2];
        size_t location1 = locateMap[id1],location2 = locateMap[id2];
        VertexPair verticesForward = std::make_pair(id1,id2);
        VertexPair verticesBackward = std::make_pair(id2,id1);
        if (edgeTable.containKey(verticesForward)){
            //graph[location1].pop();
            edgeTable.removeNode(verticesForward,graph[location1].refSize());
        }
        if (edgeTable.containKey(verticesBackward)){
            //graph[location2].pop();
            edgeTable.removeNode(verticesBackward,graph[location2].refSize());
        }
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
