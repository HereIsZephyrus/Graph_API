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
    };
    struct Message{
        enum {add = true,remove = false} type;
        EdgeInfo edge;
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
    void remove(size_t location,EdgeTable& edgeTable);
public:
    explicit WUSGraph(int v): vertexSize(v),vertexNum(0),vertexCounter(0){graph.reserve(v);}
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
    void kruskal() {
        DisjSets ds(graph.vertexCount());
        ProcessMessage();
        for (const auto& edge : edges) {
            int root1 = ds.find(graph.alias[edge.vertex1]);
            int root2 = ds.find(graph.alias[edge.vertex2]);
            if (root1 != root2) {
                mstEdges.push_back(edge);
                totalWeight += edge.weight;
                ds.unionSets(root1, root2);
            }
        }
    }

    const Vector<Edge>& getMSTEdges() const {return mstEdges;}
    W getTotalWeight() const {return totalWeight;}
};
}
#include "graph.tpp"
#endif /* graph_hpp */
