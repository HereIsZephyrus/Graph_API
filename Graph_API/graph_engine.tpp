//
//  graph_engine1.cpp
//  Graph_API
//
//  Created by ChanningTong on 1/1/25.
//

template <typename W>
std::shared_ptr<CityPoints> BuildVisualPoints(WUSG::Graph<W>& graph){
    std::vector<Point> vertices;
    vertices.reserve(graph.vertexCount());
    static constexpr glm::vec3 cityColor = glm::vec3(1.0,1.0,1.0);
    auto visit = [](const WUSG::Vertex<W>& node,std::vector<Point>* verticesArray){
        W x = node.x, y = node.y;
        verticesArray->push_back(Point(glm::vec3(x,y,0.0),cityColor));
    };
    auto binded = std::bind(visit, std::placeholders::_1, &vertices);
    WUSG::BFS(graph, graph.getStartVertex(), binded);
    return std::make_shared<CityPoints>(vertices,0.05,cityColor);
}
