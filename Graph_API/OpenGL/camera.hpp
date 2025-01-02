//
//  camera.hpp
//  RSimageprocess
//
//  Created by ChanningTong on 12/10/24.
//

#ifndef camera_hpp
#define camera_hpp

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Extent{
    GLfloat left,right,top,botton;
    Extent():left(std::numeric_limits<GLfloat>::max()),right(-std::numeric_limits<GLfloat>::max()),top(-std::numeric_limits<GLfloat>::max()),botton(std::numeric_limits<GLfloat>::max()){}
    Extent(GLfloat l,GLfloat r,GLfloat t,GLfloat b):left(l),right(r),botton(b),top(t){}
};
class Camera2D {
public:
    static Camera2D& getView(){
        static Camera2D instance;
        return instance;
    }
    void processKeyboard(GLFWwindow* window);
    void processScroll(GLFWwindow* window, double xoffset, double yoffset, bool pressCtrl, bool pressAlt);
    void zoomInOut(float yOffset);
    glm::mat4 getProjectionMatrix() const {return projectionMatrix;}
    glm::mat4 getViewMatrix() const {return viewMatrix;}
    float getZoom() const {return zoom;}
    glm::vec2 getPosition() const {return position;}
    GLfloat getCameraSpeed(GLfloat speed) const {return speed * deltaTime / zoom;}
    void setDeltaPosition(glm::vec2 previewPosition,GLfloat x,GLfloat y){
        position.x = previewPosition.x + x;
        position.y = previewPosition.y + y;
        updateViewMatrix();
    }
    void setExtent(Extent extent);
    void updateProjectionMatrix(GLfloat width,GLfloat height);
    void updateViewMatrix() ;
    double normal2worldX(GLdouble normalX);
    double normal2worldY(GLdouble normalY);
private:
    Camera2D();
    glm::vec2 position;
    float zoom,extentZoom;
    glm::mat4 projectionMatrix,viewMatrix;
    const GLfloat marginRate = 1.05;
    const GLfloat deltaTime = 0.016f; // 60FPS
    Extent extent;
    static constexpr int worldRateFactor = 100;
};

#endif /* camera_hpp */
