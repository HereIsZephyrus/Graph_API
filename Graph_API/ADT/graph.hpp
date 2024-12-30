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
#include "disjsets.hpp"
#include "heap.hpp"
#include "tree.hpp"
using std::string;
namespace tcb {
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
    struct Message{
        enum {add = true,remove = false} type;
        EdgeInfo edge;
        bool operator==(const Message& other) const {
            return type == other.type && edge == other.edge;
        }
    };
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
    void remove(size_t location,EdgeTable& edgeTable){
        AdjList& delList = graph[location];
        for (typename AdjList::iterator orientEdge = delList.begin(); orientEdge!= delList.end(); orientEdge++){
            //pEdge orientEdge = it->data;
            if (!alias.containKey(orientEdge->data.orient))
                continue;
            pEdge friendEdge = orientEdge->data.friendEdge;
            int orientID = alias[orientEdge->data.orient];
            VertexPair verticesForward = std::make_pair(delList.vertexID,orientID); //I can't use it->weight since weight is not the member of Node but the menber of data,how to overload?
            VertexPair verticesBackward = std::make_pair(orientID,delList.vertexID);
            W weight;
            if (edgeTable.containKey(verticesForward)){
                weight = edgeTable[verticesForward]->data.weight;
                EdgeInfo edgeInfo(verticesForward,weight);
                MST.PushMessage(Message(Message::remove,edgeInfo));
                edgeTable.remove(verticesForward);
            }
            if (edgeTable.containKey(verticesBackward)){
                weight = edgeTable[verticesBackward]->data.weight;
                EdgeInfo edgeInfo(verticesBackward,weight);
                MST.PushMessage(Message(Message::remove,edgeInfo));
                edgeTable.remove(verticesBackward);
            }
            AdjList& oriList = graph[locateMap[orientID]];
            int count = 0;
            for (typename AdjList::iterator it = oriList.begin(); it != oriList.end(); it++)
                ++count;
            if (oriList.getSize() != count)
                std::cout<<oriList.getSize()<<' '<<count<<std::endl;
            oriList.pop();
            if (friendEdge != nullptr){ //why some destryed friendEdge will remain as empty?
                friendEdge->prev->next = friendEdge->next;
                friendEdge->next->prev = friendEdge->prev;
                count = 0;
                for (typename AdjList::iterator it = oriList.begin(); it != oriList.end(); it++)
                    ++count;
                if (oriList.getSize() != count)
                    std::cout<<oriList.getSize()<<' '<<count<<std::endl;
                delete friendEdge;
                friendEdge = nullptr;
            }
        }
        delList.clear();
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
    void addEdge(V v1,V v2,W weight){
        if (!alias.containKey(v1) || !alias.containKey(v2))
            return;
        int id1 = alias[v1], id2 = alias[v2];
        size_t location1 = locateMap[id1],location2 = locateMap[id2];
        pEdge edge1 = new Node(Edge(v2,weight));
        pEdge edge2 = new Node(Edge(v1,weight));
        edge1->data.friendEdge = edge2;   edge2->data.friendEdge = edge1;
        graph[location1].insert(edge1);    graph[location2].insert(edge2);
        VertexPair vertices = std::make_pair(id1,id2);
        edgeTable.insert(vertices, edge1);
        EdgeInfo edgeInfo(vertices,weight);
        MST.PushMessage(Message(Message::add,edgeInfo));
    }
    void removeEdge(V v1,V v2);
    bool hasEdge(V v1,V v2) const;
    W getWeight(V v1,V v2) const;
    Neighbor getNeighbor(V checkNode);
    const Vector<EdgeInfo>& getMST(){
        MST.calcMST();
        return MST.getMSTEdges();
    }
    W getMSTWeight() {return MST.getTotalWeight();}
    void debug(){
        for (int i = 0; i < graph.getSize(); i++){
            AdjList& list = graph[i];
            int count = 0;
            for (typename AdjList::iterator it = list.begin(); it != list.end(); it++){
                ++count;
            }
            if (list.getSize() != count)
                std::cout<<i<<' '<<list.getSize() <<' ' << count<<std::endl;
        }
    }
};
template <typename V, typename W>
class WUSGraph<V,W>::MinSpanForest{
    Queue<Message> MsgQue;
    Vector<EdgeInfo> mstEdges;
    W totalWeight;
    AVLSearchTree<EdgeInfo> edges;
    WUSGraph& graph;
    void ProcessMessage(){
        while (!MsgQue.isEmpty()) {
            Message msg = MsgQue.front();
            MsgQue.dequeue();
            if (msg.type == Message::add)
                edges.insert(msg.edge);
            else
                edges.remove(msg.edge);
        }
    }
public:
    MinSpanForest(WUSGraph& graph) : totalWeight(0),graph(graph) {}
    void PushMessage(const Message& Message) {MsgQue.enqueue(Message);}
    void calcMST() {
        if (MsgQue.isEmpty())
            return;
        DisjSets ds(static_cast<int>(graph.vertexCount()));
        ProcessMessage();
        Queue<EdgeInfo> addedEdge;
        addedEdge.clear();
        mstEdges.clear();
        totalWeight = 0;
        while (mstEdges.getSize() < graph.vertexCount() - 1) {
            EdgeInfo edge = edges.findMin();
            addedEdge.enqueue(edge);
            edges.remove(edge);
            int uset = ds.find(static_cast<int>(graph.locateMap[edge.vertex.first]));
            int vset = ds.find(static_cast<int>(graph.locateMap[edge.vertex.second]));
            if (uset != vset) {
                mstEdges.push_back(edge);
                totalWeight += edge.weight;
                ds.unionSets(uset, vset);
            }
        }
        while (!addedEdge.isEmpty()){
            edges.insert(addedEdge.front());
            addedEdge.dequeue();
        }
    }
    const Vector<EdgeInfo>& getMSTEdges() const {return mstEdges;}
    W getTotalWeight() {
        calcMST();
        return totalWeight;
    }
};
}
#include "graph.tpp"
#endif /* graph_hpp */
