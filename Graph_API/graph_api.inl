//
//  graph_api.cpp
//  Graph_API
//
//  Created by ChanningTong on 12/29/24.
//

#ifndef graph_api_inl
#define graph_api_inl
namespace WUSG{
template <typename W>
void CreateGraphFromFile(const string& filename, WUSGraph<string,W>& graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file");
    }
    string line;
    int numVertices, numEdges;
    std::getline(file, line);
    std::istringstream(line) >> numVertices;
    std::getline(file, line);
    std::istringstream(line) >> numEdges;
    for (int i = 0; i < numVertices; ++i) {
        std::getline(file, line);
        graph.addVertex(line);
    }
    for (int i = 0; i < numEdges; ++i) {
        std::getline(file, line);
        std::istringstream iss(line);
        string vertex1, vertex2;
        double weight;
        iss >> vertex1 >> vertex2 >> weight;
        graph.addEdge(vertex1, vertex2, weight);
    }
    file.close();
}
template <typename W>
void CreateGraphFromFile(const string& filename, Graph<W>& graph){
    using V = Vertex<W>;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file");
    }
    string line;
    int numVertices, numEdges;
    std::getline(file, line);
    std::istringstream(line) >> numVertices >> numEdges;
    for (int i = 0; i < numVertices; ++i) {
        std::getline(file, line);
        int id;
        W x,y;
        std::istringstream(line) >> id >> x >> y; 
        graph.addVertex(Vertex<W>(id,x,y));
    }
    for (int i = 0; i < numEdges; ++i) {
        std::getline(file, line);
        int vertex1, vertex2;
        std::istringstream(line) >> vertex1 >> vertex2;
        V v1 = graph.getVertex(vertex1), v2 = graph.getVertex(vertex2);
        W weight = sqrt(pow(v1.x - v2.x,2) + pow(v1.y - v2.y,2));
        graph.addEdge(v1,v2,weight);
    }
}
template <typename V, typename W>
int MaxDegree(const WUSGraph<V,W>& graph){
    std::set<string> vertices = graph.getVertice();
    int maxDegree = 0;
    for (std::set<string>::const_iterator vertex = vertices.begin(); vertex != vertices.end(); vertex++){
        int degree = graph.getDegree(*vertex);
        if (degree > maxDegree)
            maxDegree = degree;
    }
    return maxDegree;
}
template <typename V, typename W, typename Func>
void DFS(WUSGraph<V,W>& graph, const V& startNode, Func func){
    graph.WalkThrough(startNode, WalkMethod::DFS, func);
}
template <typename V, typename W, typename Func>
void BFS(WUSGraph<V,W>& graph, const V& startNode, Func func){
    graph.WalkThrough(startNode, WalkMethod::BFS, func);
}
template <typename V, typename W>
double Steiner(const WUSGraph<V,W>& graph,const Vector<V>& keyVertices){
    return graph.steinerTree(keyVertices);
}
template <typename V, typename W>
Vector<std::pair<V,V>> Prim(WUSGraph<V,W>& graph){
    return graph.calcMST();
}
template <typename V, typename W>
void Print(const WUSGraph<V,W>& graph,ostream& os){os<<graph;}
}
#endif
