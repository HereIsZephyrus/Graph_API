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
#include "graphing.hpp"
#include "window.hpp"
#include "camera.hpp"
#include "commander.hpp"
#include "graph_api.hpp"
#include "base.hpp"

using VertexVec = Vector<std::pair<base::Vertex<valueType>,base::Vertex<valueType>>>;
class SpatialPrimitive : public Primitive{
    std::shared_ptr<QuadTree<size_t>> indexTree;
protected:
    std::vector<size_t> searchWindow(float x,float y,valueType windowSize = 200){
        SpatialRange range = SpatialRange(x - windowSize / 2,y - windowSize / 2,windowSize,windowSize);
        return indexTree->queryRange(range);
    }
    SpatialPrimitive(const std::vector<Point>& inputVertex,GLenum shp,Shader* shader, int elementSize);
    void insert(float x,float y,size_t index){indexTree->insert(x,y,index);}
    void remove(float x,float y){indexTree->remove(x,y);}
    void clear(){indexTree->clear();}
};
namespace transport{
constexpr glm::vec3 cityColor = glm::vec3(1.0,0.63,0.48);
constexpr glm::vec3 roadColor = glm::vec3(0.69,0.93,0.94);
class CityPoints : public SpatialPrimitive{
    static constexpr double clickRange = 1;
public:
    CityPoints(const std::vector<Point>& inputVertex,GLfloat r,std::vector<int>& ID):
    SpatialPrimitive(inputVertex,GL_POINTS,ShaderBucket["ball"].get(),1),radius(r){
        vertexID = std::move(ID);
    }
    void draw() const override;
    int getClick(double x,double y);
    std::vector<int> getBuffer(double sx,double sy,double tx, double ty);
    void remove(double x,double y,int id);
    void insert(double x,double y,int id);
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
    void remove(double x,double y,int id1,int id2);
    void insert(base::Vertex<valueType> v1,base::Vertex<valueType> v2);
private:
    GLfloat thickness;
    std::vector<VertexPair> vertexID;
};
template <typename W>
class Node{
public:
    using CityNode = WUSG::Vertex<W>;
    CityNode city;
    struct RoadNode{   
        CityNode vertex1, vertex2;
        W weight;
        RoadNode(const CityNode& v1, const CityNode& v2, W w): vertex1(v1),vertex2(v2),weight(w){}
        RoadNode() = default;
    }road;
private:
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
    bool isCityNode() const {return state == isCity;}
    void draw(){
        if (state == isCity)     drawCity();
        else                     drawRoad();
    }
    std::string printInfo(){
        if (state == isCity)     return printCity();
        else                     return printRoad();
    }
    CityNode getCity() const {return city;}
    RoadNode getRoad() const {return road;}
};
class RouteSystem{
public:
    static RouteSystem& getSystem(){
        static RouteSystem instance;
        return instance;
    }
    std::shared_ptr<CityPoints> citys;
    std::shared_ptr<Roads> roads;
    std::shared_ptr<WUSG::Graph<valueType>> graph;
    std::shared_ptr<Primitive> feature;
    Vector<base::Vertex<valueType>> keyVertices;
    void ImportData(const std::string& filePath);
    void Draw();
    void CreateFeature(Vector<std::pair<base::Vertex<valueType>,base::Vertex<valueType>>>& vertices);
    void CreateFeature(Vector<base::Vertex<valueType>>& vertices);
private:
    RouteSystem():citys(nullptr),roads(nullptr),graph(nullptr),feature(nullptr){}
    static constexpr glm::vec3 featureRoadColor{0.58,0.0,0.83};
    static constexpr glm::vec3 featureCityColor{0.0,0.54,0.0};
};

std::shared_ptr<CityPoints> BuildVisualPoints(WUSG::Graph<valueType>& graph);
std::shared_ptr<Roads> BuildVisualRoads(WUSG::Graph<valueType>& graph);
void processOperator(GLFWwindow* window);
void processMouse();
}
namespace gui{
void processWorkspace();
bool DrawPopup();
void ImportData();
void AddPoint();
void AddEdge(base::Vertex<valueType> termNode);
void PlanRoute();
void CalcShortestPath(base::Vertex<valueType> termNode);
void SearchCity();
void SearchRoad();
void GetBuffer(double termX, double termY);
}
#include "graph_engine.tpp"
#endif /* graph_engine_h */
