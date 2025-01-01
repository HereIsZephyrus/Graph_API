//
//  window.cpp
//  data_structure
//
//  Created by ChanningTong on 10/21/24.
//

#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <glm/glm.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "window.hpp"
#include "graphing.hpp"

GLfloat WindowParas::screen2normalX(GLdouble screenX){
    return  (2.0f * static_cast<GLfloat>(screenX/ SCREEN_WIDTH * xScale)) - 1.0f;
}
GLfloat WindowParas::screen2normalY(GLdouble screenY){
    return 1.0f - (2.0f * static_cast<GLfloat>(screenY / SCREEN_HEIGHT * yScale));
}
GLfloat WindowParas::normal2orthoX(GLfloat normalX){
    GLfloat left = -SCREEN_WIDTH / xScale / 2.0f;
    GLfloat right = SCREEN_WIDTH / xScale / 2.0f;
    return  left + (right - left) * (normalX + 1) / 2;
}
GLfloat WindowParas::normal2orthoY(GLfloat normalY){
    GLfloat button = -SCREEN_HEIGHT / yScale / 2.0f;
    GLfloat top = SCREEN_HEIGHT / yScale / 2.0f;
    return  button + (top - button) * (normalY + 1) / 2;
}
int initOpenGL(GLFWwindow *&window,std::string windowName) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    WindowParas& windowPara = WindowParas::getInstance();
    window = glfwCreateWindow(windowPara.WINDOW_WIDTH, windowPara.WINDOW_HEIGHT, windowName.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwGetWindowContentScale(window, &windowPara.xScale, &windowPara.yScale);
    //std::cout<<"This Screen xScale is "<<windowPara.xScale<<",yScale is "<<windowPara.yScale<<std::endl;
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit()){
        std::cerr << "Failed to initialize GLEW"<<std::endl;
        return -2;
    }
    windowPara.defaultAlpha = glfwGetWindowOpacity(window);
    glfwGetFramebufferSize(window, &windowPara.SCREEN_WIDTH, &windowPara.SCREEN_HEIGHT);
    glViewport(0, 0, windowPara.SCREEN_WIDTH, windowPara.SCREEN_HEIGHT);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_MULTISAMPLE);
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout<<version<<std::endl;
    HAS_INIT_OPENGL_CONTEXT = true;
    return 0;
}
int initImGUI(GLFWwindow *window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsLight();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
    return  0;
}
