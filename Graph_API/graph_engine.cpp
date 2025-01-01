//
//  graph_engine.cpp
//  Graph_API
//
//  Created by ChanningTong on 1/1/25.
//

#include <vector>
#include <memory>
#include "graph_engine.hpp"
void CityPoints::draw() const{
    shader ->use();
    GLuint radiusLoc = glGetUniformLocation(shader->program, "radius");
    GLuint transparentLoc = glGetUniformLocation(shader->program, "transparent");
    glUniform1f(radiusLoc,radius);
    glUniform1f(transparentLoc,1.0f);
    glBindVertexArray(VAO);
    glDrawArrays(shape, 0, static_cast<GLsizei>(vertexNum));
    glBindVertexArray(0);
}
