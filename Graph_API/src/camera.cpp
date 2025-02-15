//
//  camera.cpp
//  RSimageprocess
//
//  Created by ChanningTong on 12/10/24.
//

#include "camera.hpp"
#include "window.hpp"
#include "commander.hpp"
void Camera2D::processKeyboard(GLFWwindow* window) {
    BufferRecorder& buffer = BufferRecorder::getBuffer();
    const GLfloat cameraSpeed = getCameraSpeed(100.0f);
    if (buffer.pressAlt || buffer.pressCtrl|| buffer.pressShift)//ignore function input
        return;
    if (buffer.keyRecord[GLFW_KEY_W])
        position.y += cameraSpeed;
    if (buffer.keyRecord[GLFW_KEY_S])
        position.y -= cameraSpeed;
    if (buffer.keyRecord[GLFW_KEY_A])
        position.x -= cameraSpeed;
    if (buffer.keyRecord[GLFW_KEY_D])
        position.x += cameraSpeed;
    updateViewMatrix();
}
void Camera2D::processScroll(GLFWwindow* window, double xoffset, double yoffset, bool pressCtrl, bool pressAlt){
    const GLfloat cameraSpeed = getCameraSpeed(20.0f);
    double xpos,ypos;
    glfwGetCursorPos(window,&xpos,&ypos);
    WindowParas& windowPara = WindowParas::getInstance();
    if (xpos < windowPara.SIDEBAR_WIDTH)
        return;
    if (pressCtrl)//if conflict, ctrl first:yscroll
        position.y += cameraSpeed * yoffset;
    else if (pressAlt)//if conflict, then alt:xscroll
        position.x -= cameraSpeed * yoffset;
    else{
        zoomInOut(static_cast<float>(yoffset));
    }
    updateViewMatrix();
}
void Camera2D::zoomInOut(float yOffset) {
    zoom -= yOffset * 0.1f;
    if (zoom < 0.01f)
        zoom = 0.01f;
    if (zoom > 10.0f)
        zoom = 10.0f;
}
Camera2D::Camera2D() : position(0.0f, 0.0f), zoom(1.0f){
    projectionMatrix = glm::ortho(-1.0f * worldRateFactor, 1.0f * worldRateFactor, -1.0f * worldRateFactor, 1.0f * worldRateFactor, -1000.0f, 100.0f);
    viewMatrix = glm::mat4(1.0f);
}
void Camera2D::focus(double x,double y){
    position.x = x; position.y = y;
    zoom = 6;
}
void Camera2D::setExtent(Extent inputExtent){
    extent = inputExtent;
    position.x = (extent.left + extent.right) / 2;
    position.y = (extent.botton + extent.top) / 2;
    GLfloat width = extent.right - extent.left, height = extent.top - extent.botton;
    float zoomX = 2 * worldRateFactor / width, zoomY = 2 * worldRateFactor / height;
    if (zoomX < zoomY){
        zoom = zoomX;
        extent.top = position.y + width/2;
        extent.botton = position.y - width/2;
    }else{
        zoom = zoomY;
        extent.top = position.y + height/2;
        extent.botton = position.y - height/2;
    }
    extentZoom = zoom;
    updateProjectionMatrix(width,height);
    updateViewMatrix();
}
void Camera2D::updateProjectionMatrix(GLfloat width,GLfloat height){
    //projectionMatrix = glm::ortho(-width/2,width/2, - height/2,height/2, -100.0f, 100.0f);
}
void Camera2D::updateViewMatrix() {
    glm::vec3 scaling(zoom, zoom, 1.0f);
    viewMatrix = glm::mat4(1.0f);
    //viewMatrix = glm::translate(viewMatrix, glm::vec3(position, 0.0f));
    viewMatrix = glm::scale(viewMatrix, scaling);
    viewMatrix = glm::translate(viewMatrix, glm::vec3(-position, 0.0f));
}

double Camera2D::normal2worldX(GLdouble normalX){
    GLfloat width = extent.right - extent.left;
    GLfloat currentWidth = width * extentZoom / zoom;
    GLfloat currentLeft = position.x - currentWidth / 2;
    return (normalX + 1.0f) * currentWidth / 2 + currentLeft;
}
double Camera2D::normal2worldY(GLdouble normalY){
    GLfloat height = extent.top - extent.botton;
    GLfloat currentHeight = height * extentZoom / zoom;
    GLfloat currentTop = position.y + currentHeight / 2;
    return currentTop - (1.0f - normalY) * currentHeight / 2;
}
