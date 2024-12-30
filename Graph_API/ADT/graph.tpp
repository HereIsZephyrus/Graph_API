//
//  graph.cpp
//  Graph_API
//
//  Created by ChanningTong on 12/29/24.
//

using namespace tcb;
template <typename V, typename W>
struct WUSGraph<V,W>::Edge{
    V orient;
    W weight;
    pEdge friendEdge;
    Edge(V to = V(),W w = W(),pList friendList = nullptr):orient(to),weight(w),friendEdge(nullptr){}
    bool operator==(const Edge& other) const {return orient == other.orient && weight == other.weight;}
    Edge(const Edge& other) : orient(other.orient), weight(other.weight), friendEdge(other.friendEdge) {}
};
template <typename V, typename W>
class  WUSGraph<V,W>::EdgeTable : public HashMap<VertexPair, pEdge>{
public:
    pEdge removeNode(VertexPair vertices,bool oneway){
        using Bucket = HashMap<VertexPair, pEdge>::Bucket;
        pEdge orientEdge = this->getRefValue(vertices);
        pEdge ret_p = orientEdge->next;
        orientEdge->prev->next = orientEdge->next;
        orientEdge->next->prev = orientEdge->prev;
        pEdge friendEdge = orientEdge->data.friendEdge;
        if (!oneway)
            ret_p = friendEdge->next;
        if (friendEdge != nullptr){
            friendEdge->prev->next = friendEdge->next;
            friendEdge->next->prev = friendEdge->prev;
            delete friendEdge;
        }
        delete orientEdge;
        this->remove(vertices);
        return ret_p;
    }
};
template <typename V, typename W>
class  WUSGraph<V,W>::AdjList : public List<Edge>{
    friend EdgeTable;
public:
    using Node = typename List<Edge>::Node;
    using iterator = typename List<Edge>::iterator;
    using const_iterator = typename List<Edge>::const_iterator;
    int vertexID;
    V vertex;
    void insert(pEdge edge){
        Node *p = this->begin()._ptr();
        edge->prev = p->prev;
        edge->next = p;
        this->size++;
        p->prev = p->prev->next = edge;
    }
    void pop() {--this->size;}
    AdjList(V v = V(),int ID = -1):vertex(v),vertexID(ID){}
    size_t& refSize() {return this->size;}
};
template <typename V, typename W>
void WUSGraph<V,W>::remove(size_t location,EdgeTable& edgeTable){
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
            edgeTable.remove(verticesForward);
        }
        if (edgeTable.containKey(verticesBackward)){
            weight = edgeTable[verticesBackward]->data.weight;
            edgeTable.remove(verticesBackward);
        }
        EdgeInfo edgeInfo(orientEdge->data.orient,delList.vertex,weight);
        MST.PushMessage(Message(Message::remove,edgeInfo));
        if (friendEdge != nullptr && friendEdge->prev != nullptr && friendEdge->next != nullptr){ //why some destryed friendEdge will remain as empty?
            size_t loc = locateMap[orientID];
            graph[loc].pop();
            friendEdge->prev->next = friendEdge->next;
            friendEdge->next->prev = friendEdge->prev;
            delete friendEdge;
            friendEdge = nullptr;
        }
    }
    delList.clear();
}
template <typename V, typename W>
void WUSGraph<V,W>::addVertex(V newVertex){
    if (alias.containKey(newVertex))
        return;
    alias.insert(newVertex,vertexCounter);
    graph.push_back(AdjList(newVertex,vertexCounter));
    locateMap.insert(vertexCounter, vertexNum);
    ++vertexCounter;
    ++vertexNum;
}
template <typename V, typename W>
void WUSGraph<V,W>::removeVertex(V delVertex){
    if (!alias.containKey(delVertex))
        return;
    size_t location = locateMap[alias[delVertex]];
    alias.remove(delVertex);
    int backVertexID = graph.back().vertexID;
    remove(location,edgeTable);
    graph[location] = graph.back();
    graph.pop_back();
    locateMap[backVertexID] = location;
    --vertexNum;
}
template <typename V, typename W>
int WUSGraph<V,W>::getDegree(V checkVertex) const {
    if (!alias.containKey(checkVertex))
        return -1;
    size_t location = locateMap[alias[checkVertex]];
    return static_cast<int>(graph[location].getSize());
}
template <typename V, typename W>
void WUSGraph<V,W>::addEdge(V v1,V v2,W weight){
    if (!alias.containKey(v1) || !alias.containKey(v2))
        return;
    int id1 = alias[v1], id2 = alias[v2];
    size_t location1 = locateMap[id1],location2 = locateMap[id2];
    pEdge edge1 = new Node(Edge(v2,weight,&graph[id2]));
    pEdge edge2 = new Node(Edge(v1,weight,&graph[id1]));
    edge1->data.friendEdge = edge2;   edge2->data.friendEdge = edge1;
    graph[location1].insert(edge1);    graph[location2].insert(edge2);
    VertexPair vertices = std::make_pair(id1,id2);
    edgeTable.insert(vertices, edge1);
    EdgeInfo edgeInfo(v1,v2,weight);
    MST.PushMessage(Message(Message::add,edgeInfo));
}
template <typename V, typename W>
void WUSGraph<V,W>::removeEdge(V v1,V v2){
    if (!alias.containKey(v1) || !alias.containKey(v2))
        return;
    int id1 = alias[v1], id2 = alias[v2];
    size_t location1 = locateMap[id1],location2 = locateMap[id2];
    VertexPair verticesForward = std::make_pair(id1,id2);
    VertexPair verticesBackward = std::make_pair(id2,id1);
    graph[location1].pop();
    graph[location2].pop();
    W weight;
    if (edgeTable.containKey(verticesForward)){
        weight = edgeTable[verticesForward]->data.weight;
        edgeTable.removeNode(verticesForward,true);
    }
    if (edgeTable.containKey(verticesBackward)){
        weight = edgeTable[verticesBackward]->data.weight;
        edgeTable.removeNode(verticesBackward,false);
    }
    EdgeInfo edgeInfo(v1,v2,weight);
    MST.PushMessage(Message(Message::remove,edgeInfo));
}
template <typename V, typename W>
bool WUSGraph<V,W>::hasEdge(V v1,V v2) const{
    if (!alias.containKey(v1) || !alias.containKey(v2))
        return false;
    int id1 = alias[v1], id2 = alias[v2];
    VertexPair verticesForward = std::make_pair(id1,id2);
    VertexPair verticesBackward = std::make_pair(id2,id1);
    return edgeTable.containKey(verticesForward) || edgeTable.containKey(verticesBackward);
}
template <typename V, typename W>
W WUSGraph<V,W>::getWeight(V v1,V v2) const{
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
template <typename V, typename W>
WUSGraph<V,W>::Neighbor WUSGraph<V,W>::getNeighbor(V checkNode){
    Neighbor neighbors;
    const AdjList& list = graph[alias[checkNode]];
    for (typename AdjList::iterator it = list.begin(); it != list.end(); it++)
        neighbors.push_back(std::make_pair(it->data.orient, it->data.weight));
    return neighbors;
}
