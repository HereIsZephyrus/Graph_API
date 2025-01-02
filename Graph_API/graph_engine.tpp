//
//  graph_engine1.cpp
//  Graph_API
//
//  Created by ChanningTong on 1/1/25.
//

namespace transport{
template <typename W>
std::shared_ptr<CityPoints> BuildVisualPoints(WUSG::Graph<W>& graph){
    std::vector<Point> vertices;
    std::vector<int> ID;
    vertices.reserve(graph.vertexCount());
    ID.reserve(graph.vertexCount());
    static constexpr glm::vec3 cityColor = glm::vec3(1.0,0.63,0.48);
    auto visit = [](const WUSG::Vertex<W>& node,std::vector<Point>* verticesArray,std::vector<int>* IDarray){
        W x = node.x, y = node.y;
        verticesArray->push_back(Point(glm::vec3(x,y,0.0),cityColor));
        IDarray->push_back(node.id);
    };
    auto binded = std::bind(visit, std::placeholders::_1, &vertices,&ID);
    WUSG::BFS(graph, graph.getStartVertex(), binded);
    return std::make_shared<CityPoints>(vertices,0.015,ID);
}
template <typename W>
std::shared_ptr<Roads> BuildVisualRoads(WUSG::Graph<W>& graph){
    std::vector<Point> vertices;
    std::vector<VertexPair> pairArray;
    vertices.reserve(graph.edgeCount());
    static constexpr glm::vec3 roadColor = glm::vec3(0.69,0.93,0.94);
    const std::set<VertexPair>& pairs = graph.getVertexpairs();
    for (std::set<VertexPair>::const_iterator vpair = pairs.begin(); vpair != pairs.end(); vpair++){
        int id1 = vpair->first, id2 = vpair->second;
        WUSG::Vertex<W> temp1(id1),temp2(id2);
        WUSG::Vertex<W> v1(graph.getVertex(temp1)),v2(graph.getVertex(temp2));
        vertices.push_back(Point(glm::vec3(v1.x,v1.y,0.0),roadColor));
        vertices.push_back(Point(glm::vec3(v2.x,v2.y,0.0),roadColor));
        pairArray.push_back(*vpair);
    }
    return std::make_shared<Roads>(vertices,0.08,pairArray);
}
template <typename W>
void processOperator(GLFWwindow* window, const WUSG::Graph<W>& graph){
    Camera2D& camera = Camera2D::getView();
    camera.processKeyboard(window);
    processMouse(graph);
}
template <typename W>
void processMouse(const WUSG::Graph<W>& graph){
    using Node = transport::Node<W>;
    using Vertex = WUSG::Vertex<W>;
    BufferRecorder& buffer = BufferRecorder::getBuffer();
    if (buffer.pressLeft){
        glm::vec2 checkPos = buffer.checkPos;
        int ID = transport::citys->getClick(checkPos.x, checkPos.y);
        if (ID > 0){
            buffer.currentNode = std::make_shared<Node>(graph.getVertex(Vertex(ID)));
        }else{
            VertexPair pair = transport::roads->getClick(checkPos.x, checkPos.y);
            Vertex v1 = graph.getVertex(Vertex(pair.first)), v2 = graph.getVertex(Vertex(pair.second));
            if (pair.first > 0 && pair.second > 0)
                buffer.currentNode = std::make_shared<Node>(v1,v2,graph.getWeight(v1,v2));
            else
                buffer.currentNode = nullptr;
        }
        buffer.pressLeft = false;
    }
}
template <typename W>
void Node<W>::drawCity() const{
    Primitive primitive({Point(glm::vec3(city.x,city.y,0.0),clickedCityColor)},GL_POINTS,ShaderBucket["ball"].get());
    primitive.draw();
}
template <typename W>
void Node<W>::drawRoad() const{
    Primitive primitive({Point(glm::vec3(road.vertex1.x,road.vertex1.y,0.0),clickedRoadColor),
                         Point(glm::vec3(road.vertex2.x,road.vertex2.y,0.0),clickedRoadColor)},GL_LINES,ShaderBucket["line"].get());
    primitive.draw();
}
template <typename W>
std::string Node<W>::printCity() const{
    std::string name = "City: " + city.alias + " (" + std::to_string(city.id) + "):";
    std::stringstream coord;
    coord << "Coordinate: <" <<  std::fixed << std::setprecision(1) <<city.x << "," << city.y << ">";
    return name + '\n' + coord.str();
}
template <typename W>
std::string Node<W>::printRoad() const{
    std::string name = "From: " + road.vertex1.alias + " (" + std::to_string(road.vertex1.id) + ") \n to: " + road.vertex2.alias + " (" + std::to_string(road.vertex2.id) + ")";
    std::string weight = "Distance: " + std::to_string(road.weight);
    return "Road: \n" + name + '\n' + weight;
}
}
