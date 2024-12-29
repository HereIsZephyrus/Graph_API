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
template <typename V = string, typename W = double>
class WUSGraph{
    using Neighbor = Vector<std::pair<V,W>>;
    struct Edge;
    struct EdgeInfo{
        VertexPair vertex;
        W weight;
        bool operator==(const EdgeInfo& other) const {
            return vertex == other.vertex && weight == other.weight;
        }
        bool operator<(const EdgeInfo& other) const {
            return weight < other.weight;
        }
        EdgeInfo(VertexPair v = std::make_pair(0,0),W w = W()):vertex(v),weight(w){}
    };
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
    using pList = AdjList*;
    EdgeTable edgeTable;
    HashMap<V, int> alias;
    HashMap<int, size_t> locateMap;
    Vector<AdjList> graph;
    int vertexSize;
    int vertexCounter;
    size_t vertexNum;
    MinSpanForest MST;
    void remove(size_t location,EdgeTable& edgeTable);
public:
    explicit WUSGraph(int v): vertexSize(v),vertexNum(0),vertexCounter(0),MST(*this){graph.reserve(v);}
    //required
    size_t vertexCount() const {return vertexNum;}
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
        DisjSets ds(graph.vertexCount());
        ProcessMessage();
        Queue<EdgeInfo> addedEdge;
        mstEdges.clear();
        while (mstEdges.getSize() < graph.vertexCount() - 1) {
            EdgeInfo edge = edges.findMin();
            addedEdge.enqueue(edge);
            edges.remove(edge);
            int uset = ds.find(graph.locateMap[edge.vertex.first]);
            int vset = ds.find(graph.locateMap[edge.vertex.second]);
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
    const Vector<Edge>& getMSTEdges() const {return mstEdges;}
    W getTotalWeight() const {return totalWeight;}
};
}
#include "graph.tpp"
#endif /* graph_hpp */
