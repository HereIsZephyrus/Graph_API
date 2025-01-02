//
//  graph_engine.hpp
//  Graph_API
//
//  Created by ChanningTong on 1/1/25.
//

#ifndef graph_engine_h
#define graph_engine_h
#include <memory>
#include <iomanip>
#include <sstream>
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
    SpatialPrimitive(const std::vector<Point>& inputVertex,GLenum shp,Shader* shader, int elementSize);
    void insert(float x,float y,size_t index){indexTree->insert(x,y,index);}
    void clear(){indexTree->clear();}
};
namespace transport{
class CityPoints : public SpatialPrimitive{
    static constexpr double clickRange = 1;
public:
    CityPoints(const std::vector<Point>& inputVertex,GLfloat r,std::vector<int>& ID):
    SpatialPrimitive(inputVertex,GL_POINTS,ShaderBucket["ball"].get(),1),radius(r){
        vertexID = std::move(ID);
    }
    void draw() const override;
    int getClick(double x,double y);
private:
    GLfloat radius;
    std::vector<int> vertexID;
};
class Roads : public SpatialPrimitive{
    static constexpr double clickRange = 0.7;
public:
    Roads(const std::vector<Point>& inputVertex,GLfloat l,std::vector<VertexPair>& ID):
    SpatialPrimitive(inputVertex,GL_LINES,ShaderBucket["line"].get(),2),thickness(l){
        vertexID = std::move(ID);
    }
    void draw() const override;
    VertexPair getClick(double x,double y);
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
    void drawCity() const;
    void drawRoad() const;
    std::string printCity() const;
    std::string printRoad() const;
public:
    Node(CityNode city):state(isCity){
        this->city = city;
    }
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
void processMouse(const WUSG::Graph<W>& graph);
}
#include "graph_engine.tpp"
#endif /* graph_engine_h */
