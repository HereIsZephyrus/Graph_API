//
//  graph_engine.cpp
//  Graph_API
//
//  Created by ChanningTong on 1/1/25.
//

#include <vector>
#include <memory>
#include "graph_engine.hpp"

SpatialPrimitive::SpatialPrimitive(const std::vector<Point>& inputVertex,GLenum shp,Shader* shader, int elementSize):
Primitive(inputVertex,shp,shader){
    SpatialRange range = SpatialRange(extent.left,extent.botton,extent.right - extent.left,extent.top - extent.botton);
    indexTree = std::make_shared<QuadTree<size_t>>(range,10);
    for (size_t i = 0; i < vertexNum; i += elementSize){
        float x = 0,y = 0;
        for (int k = 0; k < elementSize; k++){
            size_t index = (i + k) * stride;
            x += vertices[index];
            y += vertices[index + 1];
        }
        x /= elementSize;
        y /= elementSize;
        indexTree->insert(x,y,i);
    }
}
namespace transport{
void CityPoints::draw() const{
    shader ->use();
    GLuint projectionLoc = glGetUniformLocation(shader->program, "projection");
    GLuint viewLoc = glGetUniformLocation(shader->program, "view");
    GLuint modelLoc = glGetUniformLocation(shader->program, "model");
    Camera2D& camera = Camera2D::getView();
    glm::mat4 projection = camera.getProjectionMatrix();
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 model = transMat;
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    
    GLuint radiusLoc = glGetUniformLocation(shader->program, "radius");
    GLuint transparentLoc = glGetUniformLocation(shader->program, "transparent");
    glUniform1f(radiusLoc,radius * camera.getZoom());
    glUniform1f(transparentLoc,1.0f);
    glBindVertexArray(VAO);
    glDrawArrays(shape, 0, static_cast<GLsizei>(vertexNum));
    glBindVertexArray(0);
}
int CityPoints::getClick(double x,double y){
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

void Roads::draw() const{
    shader ->use();
    GLuint projectionLoc = glGetUniformLocation(shader->program, "projection");
    GLuint viewLoc = glGetUniformLocation(shader->program, "view");
    GLuint modelLoc = glGetUniformLocation(shader->program, "model");
    Camera2D& camera = Camera2D::getView();
    glm::mat4 projection = camera.getProjectionMatrix();
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 model = transMat;
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    
    GLuint thicknessLoc = glGetUniformLocation(shader->program, "thickness");
    GLuint transparentLoc = glGetUniformLocation(shader->program, "transparent");
    glUniform1f(thicknessLoc,thickness * camera.getZoom());
    glUniform1f(transparentLoc,1.0f);
    glBindVertexArray(VAO);
    glDrawArrays(shape, 0, static_cast<GLsizei>(vertexNum));
    glBindVertexArray(0);
}
VertexPair Roads::getClick(double x,double y){
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
std::shared_ptr<CityPoints> citys = nullptr;
std::shared_ptr<Roads> roads = nullptr;
}
