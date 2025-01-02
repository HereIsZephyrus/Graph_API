//
//  graph_engine1.cpp
//  Graph_API
//
//  Created by ChanningTong on 1/1/25.
//

namespace transport{
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
    std::string name = "From: " + road.vertex1.alias + " (" + std::to_string(road.vertex1.id) + ")" + '\n' + "To:   " + road.vertex2.alias + " (" + std::to_string(road.vertex2.id) + ")";
    std::string weight = "Distance: " + std::to_string(road.weight);
    return "Road: \n" + name + '\n' + weight;
}
}
