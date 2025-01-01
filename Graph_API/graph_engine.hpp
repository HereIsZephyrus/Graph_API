//
//  graph_engine.hpp
//  Graph_API
//
//  Created by ChanningTong on 1/1/25.
//

#ifndef graph_engine_h
#define graph_engine_h
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "./OpenGL/graphing.hpp"
#include "./OpenGL/window.hpp"
#include "./OpenGL/camera.hpp"
#include "./OpenGL/commander.hpp"
#include "graph_api.hpp"

class CityPoints : public Primitive{
public:
    CityPoints(const std::vector<Point>& ballVertices,GLfloat r,glm::vec3 c):
    Primitive(ballVertices,GL_POINTS,ShaderBucket["ball"].get()),radius(r),color(c){}
    CityPoints(const Point ballVertex,GLfloat r,glm::vec3 c):
    Primitive(ballVertex,GL_POINT,ShaderBucket["ball"].get()),radius(r),color(c){}
    void draw() const override;
    GLfloat& getX(GLuint num){return vertices[num * 6];}
    GLfloat& getY(GLuint num){return vertices[num * 6 + 1];}
private:
    GLfloat radius;
    glm::vec3 color;
};
template <typename W>
std::shared_ptr<CityPoints> BuildVisualPoints(WUSG::Graph<W>& graph);
#include "graph_engine.tpp"
#endif /* graph_engine_h */
