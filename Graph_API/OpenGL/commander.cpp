//
//  commander.cpp
//  RSimageprocess
//
//  Created by ChanningTong on 12/10/24.
//

#include "commander.hpp"
#include "window.hpp"

void processOperator(GLFWwindow* window){
    Camera2D& camera = Camera2D::getView();
    camera.processKeyboard(window);
    processMouse();
}
void processMouse(){
    BufferRecorder& buffer = BufferRecorder::getBuffer();
    glm::vec2 checPos = buffer.checkPos;
    
}
void BufferRecorder::initIO(GLFWwindow* window){
    memset(keyRecord, GL_FALSE, sizeof(keyRecord));
    pressLeft = GL_FALSE;
    pressRight = GL_FALSE;
    pressAlt = GL_FALSE;
    pressShift = GL_FALSE;
    pressCtrl = GL_FALSE;
    doubleCliked = GL_FALSE;
    glfwSetKeyCallback(window, keyCallback);
    glfwSetScrollCallback(window, scrollCallback);
}
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
    BufferRecorder& buffer = BufferRecorder::getBuffer();
    Camera2D::getView().processScroll(window, xoffset, yoffset, buffer.pressCtrl, buffer.pressAlt);
}
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
    BufferRecorder& buffer = BufferRecorder::getBuffer();
    if (action == GLFW_PRESS){
        buffer.keyRecord[key] = GL_TRUE;
        if (buffer.keyRecord[GLFW_KEY_LEFT_CONTROL] || buffer.keyRecord[GLFW_KEY_RIGHT_CONTROL]) buffer.pressCtrl = GL_TRUE;
        if (buffer.keyRecord[GLFW_KEY_LEFT_SHIFT] || buffer.keyRecord[GLFW_KEY_RIGHT_SHIFT])  buffer.pressShift = GL_TRUE;
        if (buffer.keyRecord[GLFW_KEY_LEFT_ALT] || buffer.keyRecord[GLFW_KEY_RIGHT_ALT])    buffer.pressAlt = GL_TRUE;
    }
    if (action == GLFW_RELEASE){
        //std::cout<<"release "<<key<<std::endl;
        buffer.keyRecord[key] = GL_FALSE;
        if (!buffer.keyRecord[GLFW_KEY_LEFT_CONTROL] && !buffer.keyRecord[GLFW_KEY_RIGHT_CONTROL]) buffer.pressCtrl = GL_FALSE;
        if (!buffer.keyRecord[GLFW_KEY_LEFT_SHIFT] && !buffer.keyRecord[GLFW_KEY_RIGHT_SHIFT])  buffer.pressShift = GL_FALSE;
        if (!buffer.keyRecord[GLFW_KEY_LEFT_ALT] && !buffer.keyRecord[GLFW_KEY_RIGHT_ALT])    buffer.pressAlt = GL_FALSE;
    }
}
void mouseCallback(GLFWwindow* window, int button, int action, int mods){
    BufferRecorder& buffer = BufferRecorder::getBuffer();
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS ){
        WindowParas& windowPara = WindowParas::getInstance();
        GLdouble xpos,ypos;
        glfwGetCursorPos(windowPara.window, &xpos, &ypos);
        float normalX = windowPara.screen2normalX(xpos), normalY = windowPara.screen2normalY(ypos);
        Camera2D& camera = Camera2D::getView();
        double worldX = camera.normal2worldX(normalX), worldY = camera.normal2worldY(normalY);
        buffer.pressLeft = true;
        buffer.checkPos = glm::vec2(worldX,worldY);
    }
}
