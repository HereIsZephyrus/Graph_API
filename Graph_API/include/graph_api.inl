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
void CreateGraphFromFile(const string& filename, WUSGraph<string,W>& graph,bool BatchRead = false) {
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
void CreateGraphFromFile(const string& filename, Graph<W>& graph,bool BatchRead = false) {
    using V = Vertex<W>;
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Unable to open file");
    int numVertices, numEdges;
    if (BatchRead){
        static constexpr int bufferSize = 2048;
        static constexpr int maxLineSize = 200;
        int currentVertex = 0, currentEdge = 0;
        bool gap = false;
        std::streampos filePos = file.tellg();
        std::vector<char> buffer(bufferSize);
        file.read(buffer.data(), bufferSize);
        std::istringstream iss(buffer.data());
        iss >> numVertices >> numEdges;
        while (iss.str().size() >= maxLineSize){
            std::streampos pos;
            while (iss){
                pos = iss.tellg();
                if (pos > bufferSize - maxLineSize)
                    break;
                if (currentVertex < numVertices) {
                    int id;
                    W x, y;
                    iss >> id >> x >> y;
                    graph.addVertex(V(id, x, y));
                    ++currentVertex;
                }else if (!gap){
                    string line;
                    std::getline(file, line);
                    gap = true;
                }else if (currentEdge < numEdges){
                    int vertex1, vertex2;
                    iss >> vertex1 >> vertex2;
                    V temp1 = V(vertex1), temp2 = V(vertex2);
                    V v1 = graph.getVertex(temp1), v2 = graph.getVertex(temp2);
                    W weight = sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
                    graph.addEdge(v1, v2, weight);
                    ++currentEdge;
                }else
                    return;
            }
            filePos += pos;
            file.seekg(filePos);
            file.read(buffer.data(), bufferSize);
            iss = std::istringstream(buffer.data());
        }
    }
    else{
        string line;
        std::getline(file, line);
        std::istringstream(line) >> numVertices >> numEdges;
        for (int i = 0; i < numVertices; ++i) {
            std::getline(file, line);
            int id;
            W x,y;
            std::istringstream(line) >> id >> x >> y; 
            graph.addVertex(Vertex<W>(id,x,y));
        }
        std::getline(file, line);
        for (int i = 0; i < numEdges; ++i) {
            std::getline(file, line);
            int vertex1, vertex2;
            std::istringstream(line) >> vertex1 >> vertex2;
            V temp1 = V(vertex1), temp2 = V(vertex2);
            V v1 = graph.getVertex(temp1), v2 = graph.getVertex(temp2);
            W weight = sqrt(pow(v1.x - v2.x,2) + pow(v1.y - v2.y,2));
            graph.addEdge(v1,v2,weight);
        }
    }
}
template <typename V, typename W>
int MaxDegree(const WUSGraph<V,W>& graph){
    std::set<V> vertices = graph.getVertice();
    int maxDegree = 0;
    for (typename std::set<V>::const_iterator vertex = vertices.begin(); vertex != vertices.end(); vertex++){
        int degree = graph.getDegree(*vertex);
        if (degree > maxDegree)
            maxDegree = degree;
    }
    return maxDegree;
}
template <typename V, typename W>
double Sparseness(const WUSGraph<V,W>& graph){
    int totalDegree = 0;
    int vertexNum = static_cast<int>(graph.vertexCount());
    for (size_t i = 0; i < graph.vertexCount(); i++)
        totalDegree += graph.getDegree(i);
    return static_cast<double>(totalDegree) / ((vertexNum) * (vertexNum - 1));
}
template <typename V, typename W>
int CalcConnectCompoent(WUSGraph<V,W>& graph){
    return graph.countConnectedComponents();
}
template <typename V, typename W>
W ShortestPath(WUSGraph<V,W>& graph,V startNode,V termNode,Vector<std::pair<V,V>>& vertices){
    return graph.calcDistace(startNode, termNode,vertices);
}
template <typename V, typename W>
std::string GetNeighbor(const WUSGraph<V,W>& graph,V node){
    std::stringstream res;
    res << std::fixed << std::setprecision(2);
    using Neighbor = typename tcb::WUSGraph<V,W>::Neighbor;
    Neighbor neighbors = graph.getNeighbor(node);
    for (typename Neighbor::iterator it = neighbors.begin(); it != neighbors.end(); it++){
        res << "到相邻城市" << it->first.alias << "的距离是" << it->second<<'\n';
    }
    return res.str();
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
double Steiner(WUSGraph<V,W>& graph,const Vector<V>& keyVertices){
    return graph.steinerTree(keyVertices);
}
template <typename V, typename W>
W Prim(WUSGraph<V,W>& graph,Vector<std::pair<V,V>>& vertices,V startNode){
    return graph.calcMST(startNode,vertices);
}
template <typename V, typename W>
void Print(const WUSGraph<V,W>& graph,ostream& os){os<<graph;}
}
#endif
