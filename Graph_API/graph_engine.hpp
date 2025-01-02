//
//  graph_engine.hpp
//  Graph_API
//
//  Created by ChanningTong on 1/1/25.
//

#ifndef graph_engine_h
#define graph_engine_h
#include <memory>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "./OpenGL/graphing.hpp"
#include "./OpenGL/window.hpp"
#include "./OpenGL/camera.hpp"
#include "./OpenGL/commander.hpp"
#include "graph_api.hpp"

class SpatialPrimitive : public Primitive{
    std::shared_ptr<QuadTree<size_t>> indexTree;
    static constexpr int windowSize = 200;
protected:
        std::vector<size_t> searchWindow(float x,float y){
        SpatialRange range = SpatialRange(x - windowSize / 2,y - windowSize / 2,windowSize,windowSize);
        return indexTree->queryRange(range);
    }
public:
    SpatialPrimitive(const std::vector<Point>& inputVertex,GLenum shp,Shader* shader, int elementSize):
    Primitive(inputVertex,shp,shader){
        SpatialRange range = SpatialRange(extent.left,extent.botton,extent.right - extent.left,extent.top - extent.botton);
        int indexNum = static_cast<int>(vertexNum / elementSize);
        indexTree = std::make_shared<QuadTree<size_t>>(range,indexNum);
        for (size_t i = 0; i < vertexNum; i += elementSize){
            size_t index = i * stride;
            float x = 0,y = 0;
            for (int k = 0; k < elementSize; k++){
                x += vertices[index + k];
                y += vertices[index + k + 1];
            }
            x /= elementSize;
            y /= elementSize;
            indexTree->insert(x,y,i);
        }
    }
    void insert(float x,float y,size_t index){indexTree->insert(x,y,index);}
    void clear(){indexTree->clear();}
};
namespace transport{
class CityPoints : public SpatialPrimitive{
    static constexpr double clickRange = 10;
public:
    CityPoints(const std::vector<Point>& inputVertex,GLfloat r,std::vector<int>& ID):
    SpatialPrimitive(inputVertex,GL_POINTS,ShaderBucket["ball"].get(),1),radius(r){
        vertexID = std::move(ID);
    }
    void draw() const override;
    int getClick(double x,double y){
        std::vector<size_t> result = searchWindow(x,y);
        int id = -1;
        if (result.empty())
            return id;
        float distance = std::numeric_limits<float>::max();
        for (std::vector<size_t>::iterator it = result.begin(); it != result.end(); it++){
            size_t index = *it;
            float px = vertices[index * stride],py = vertices[index * stride + 1];
            float pdis = std::abs(px - x) + std::abs(py - y);
            if (pdis < clickRange * 2 && pdis < distance){ // get the nearest point
                distance = pdis;
                id = vertexID[index];
            }
        }
        return id;
    }
private:
    GLfloat radius;
    std::vector<int> vertexID;
};
class Roads : public SpatialPrimitive{
    static constexpr double clickRange = 5;
public:
    Roads(const std::vector<Point>& inputVertex,GLfloat l,std::vector<VertexPair>& ID):
    SpatialPrimitive(inputVertex,GL_LINES,ShaderBucket["line"].get(),2),thickness(l){
        vertexID = std::move(ID);
    }
    void draw() const override;
    VertexPair getClick(double x,double y){
        std::vector<size_t> result = searchWindow(x,y);
        VertexPair id = std::make_pair(-1,-1);
        if (result.empty())
            return id;
        float distance = std::numeric_limits<float>::max();
        for (std::vector<size_t>::iterator it = result.begin(); it != result.end(); it++){
            size_t index1 = *it,index2 = *it + 1;
            float px1 = vertices[index1 * stride],py1 = vertices[index1 * stride + 1];
            float px2 = vertices[index2 * stride],py2 = vertices[index2 * stride + 1];
            float A = py2 - py1;
            float B = px1 - px2;
            float C = px2 * py1 - px1 * py2;
            float distanceToLine = std::abs(A * x + B * y + C) / std::sqrt(A * A + B * B);
            if (distanceToLine < clickRange) {
                float lineLength = std::sqrt((px2 - px1) * (px2 - px1) + (py2 - py1) * (py2 - py1));
                float projection = ((x - px1) * (px2 - px1) + (y - py1) * (py2 - py1)) / lineLength;
                if (projection >= 0 && projection <= lineLength) {
                    distance = distanceToLine;
                    id = vertexID[index1 / 2];
                }
            }
        }
        return id;
    }
private:
    GLfloat thickness;
    std::vector<VertexPair> vertexID;
};
template <typename W>
class Node{
    using CityNode = WUSG::Vertex<W>;
    CityNode city;
    struct RoadNode{   
        CityNode vertex1, vertex2;
        W weight;
    }road;
    enum : bool{isCity = false, isRoad = true} state;
    static constexpr glm::vec3 clickedCityColor = glm::vec3(1.0,0.0,0.0);
    static constexpr glm::vec3 clickedRoadColor = glm::vec3(0.0,0.0,1.0);
    void drawCity() const{
        Primitive primitive({Point(glm::vec3(city.x,city.y,0.0),clickedCityColor)},GL_POINTS,ShaderBucket["ball"].get());
        primitive.draw();
    }
    void drawRoad() const{
        Primitive primitive({Point(glm::vec3(road.vertex1.x,road.vertex1.y,0.0),clickedRoadColor),
                             Point(glm::vec3(road.vertex2.x,road.vertex2.y,0.0),clickedRoadColor)},GL_LINES,ShaderBucket["line"].get());
        primitive.draw();
    }
    std::string printCity() const{
        std::string name = "City: " + city.alias + " (" + std::to_string(city.id) + ")";
        std::string coord = "Coordinate: <" + std::to_string(city.x) + "," + std::to_string(city.y) + ">";
        return name + '\n' + coord;
    }
    std::string printRoad() const{
        std::string name = "Road: " + road.vertex1.alias + " (" + std::to_string(road.vertex1.id) + ") - " + road.vertex2.alias + " (" + std::to_string(road.vertex2.id) + ")";
        std::string weight = "Distance: " + std::to_string(road.weight);
        return name + '\n' + weight;
    }
public:
    Node(CityNode city):state(isCity){city = city;}
    Node(CityNode city1, CityNode city2, W distance):state(isRoad){road = RoadNode(city1,city2,distance);}
    void draw(){
        if (state == isCity)
            drawCity();
        else
            drawRoad();
    }
    std::string printInfo(){
        if (state == isCity)
            return printCity();
        else
            return printRoad();
    }
};
extern std::shared_ptr<CityPoints> citys;
extern std::shared_ptr<Roads> roads;

template <typename W>
std::shared_ptr<CityPoints> BuildVisualPoints(WUSG::Graph<W>& graph);
template <typename W>
std::shared_ptr<Roads> BuildVisualRoads(WUSG::Graph<W>& graph);
template <typename W>
void processOperator(GLFWwindow* window, const WUSG::Graph<W>& graph);
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

}
#include "graph_engine.tpp"
#endif /* graph_engine_h */
