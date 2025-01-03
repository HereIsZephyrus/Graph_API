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
#include "window.hpp"
#include "graphing.hpp"
#include "commander.hpp"
#include "../graph_engine.hpp"

void WindowParas::InitParas(){
    glfwGetWindowContentScale(window, &xScale, &yScale);
    SCREEN_LEFT = SIDEBAR_WIDTH ;   SCREEN_BOTTON = 0;
    SCREEN_WIDTH = WINDOW_WIDTH * xScale - SCREEN_LEFT * xScale;   SCREEN_HEIGHT = WINDOW_HEIGHT * yScale - SCREEN_BOTTON * yScale;
}
GLfloat WindowParas::screen2normalX(GLdouble screenX){
    return  (2.0f * static_cast<GLfloat>((screenX - SCREEN_LEFT)/ SCREEN_WIDTH * xScale)) - 1.0f;
}
GLfloat WindowParas::screen2normalY(GLdouble screenY){
    return 1.0f - (2.0f * static_cast<GLfloat>((screenY - SCREEN_BOTTON) / SCREEN_HEIGHT * yScale));
}
void windowPosChangeCallback(GLFWwindow* window, int xpos, int ypos){
    WindowParas& windowPara = WindowParas::getInstance();
    glViewport(windowPara.SCREEN_LEFT * windowPara.xScale, windowPara.SCREEN_BOTTON * windowPara.yScale, windowPara.SCREEN_WIDTH, windowPara.SCREEN_HEIGHT);
}
void windowRefreshCallback(GLFWwindow* window){
    WindowParas& windowPara = WindowParas::getInstance();
    glViewport(windowPara.SCREEN_LEFT * windowPara.xScale, windowPara.SCREEN_BOTTON * windowPara.yScale, windowPara.SCREEN_WIDTH, windowPara.SCREEN_HEIGHT);
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
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit()){
        std::cerr << "Failed to initialize GLEW"<<std::endl;
        return -2;
    }
    windowPara.InitParas();
    glViewport(windowPara.SCREEN_LEFT * windowPara.xScale, windowPara.SCREEN_BOTTON * windowPara.yScale, windowPara.SCREEN_WIDTH, windowPara.SCREEN_HEIGHT);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_MULTISAMPLE);
    const GLubyte* version = glGetString(GL_VERSION);
    glfwSetWindowPosCallback(window, windowPosChangeCallback);
    glfwSetWindowRefreshCallback(window, windowRefreshCallback);
    std::cout<<version<<std::endl;
    HAS_INIT_OPENGL_CONTEXT = true;
    GLint maxTextureSize;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
    std::cout << "Maximum texture size: " << maxTextureSize << std::endl;
    return 0;
}
namespace gui {
ImFont *englishFont = nullptr,*chineseFont = nullptr;
bool toImportData = false,toAddPoint = false,toCalcMaxDegree = false,toCalcSparse = false,toCalcConeectCompoent = false,toSearchCity = false,toSearchRoad = false,toCalcShortestPath = false,toGetNeighbor = false,toGetBuffer = false,toPlanRoute = false,toCalcMST = false,toDeleteObject = false;
int Initialization(GLFWwindow *window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
    englishFont = io.Fonts->AddFontFromFileTTF("/Users/channingtong/Program/Graph_API/ImGUIopengl3/Arial.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesDefault());
    chineseFont = io.Fonts->AddFontFromFileTTF("/Users/channingtong/Program/Graph_API/ImGUIopengl3/Songti.ttc", 20.0f,nullptr,io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    io.Fonts->Build();
    return 0;
}

void DrawBasic() {
    WindowParas& windowPara = WindowParas::getInstance();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(windowPara.SIDEBAR_WIDTH, windowPara.WINDOW_HEIGHT));
    ImGui::Begin("Sidebar", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    RenderInfoPanel();
    RenderWorkspace();
    ImGui::End();
    return;
}
void RenderInfoPanel(){
    WindowParas& windowPara = WindowParas::getInstance();
    ImGui::BeginChild("Info",ImVec2(0,windowPara.WINDOW_HEIGHT / 3));
    double cursorX, cursorY;
    glfwGetCursorPos(windowPara.window, &cursorX, &cursorY);
    float normalX = windowPara.screen2normalX(cursorX), normalY = windowPara.screen2normalY(cursorY);
    Camera2D& camera = Camera2D::getView();
    double worldX = camera.normal2worldX(normalX), worldY = camera.normal2worldY(normalY);
    ImGui::PushFont(gui::chineseFont);
    ImGui::Text("当前坐标:\n <%.1f, %.1f>", worldX, worldY);
    BufferRecorder& buffer = BufferRecorder::getBuffer();
    if (buffer.resInfo != "")
        ImGui::Text("%s", buffer.resInfo.c_str());
    if (buffer.currentNode != nullptr)
        ImGui::Text("%s", buffer.currentNode->printInfo().c_str());
    ImGui::PopFont();
    ImGui::EndChild();
}
void RenderWorkspace(){
    BufferRecorder& buffer = BufferRecorder::getBuffer();
    WindowParas& windowPara = WindowParas::getInstance();
    ImGuiStyle& style = ImGui::GetStyle();
    const ImVec2 ButtonSize = ImVec2(windowPara.SIDEBAR_WIDTH * 3 / 7, 50);
    style.FramePadding = ImVec2(6.0f, 4.0f);
    style.ItemSpacing = ImVec2(12.0f, 8.0f);
    ImGui::PushFont(gui::chineseFont);
    if (ImGui::Button("导入数据集",ButtonSize))
        toImportData = true;
    ImGui::SameLine();
    if (ImGui::Button("求最大度点",ButtonSize))
        toCalcMaxDegree = true;
    
    if (ImGui::Button("求稀疏度",ButtonSize))
        toCalcSparse = true;
    ImGui::SameLine();
    if (ImGui::Button("求连通分量",ButtonSize))
        toCalcConeectCompoent = true;
    
    if (ImGui::Button("查询城市",ButtonSize))
        toSearchCity = true;
    ImGui::SameLine();
    if (ImGui::Button("查询道路",ButtonSize))
        toSearchRoad = true;
    
    if (buffer.currentNode != nullptr){
        if (buffer.currentNode->isCityNode()){
            if (ImGui::Button("最小生成树",ButtonSize))
                toCalcMST = true;
            ImGui::SameLine();
            if (ImGui::Button("删除城市",ButtonSize))
                toDeleteObject = true;
            
            if (ImGui::Button("求最短路径",ButtonSize))
                toCalcShortestPath = true;
            ImGui::SameLine();
            if (ImGui::Button("求相邻城市",ButtonSize))
                toGetNeighbor = true;
            
            if (ImGui::Button("求缓冲区",ButtonSize))
                toGetBuffer = true;
            ImGui::SameLine();
            if (ImGui::Button("多点路线规划",ButtonSize))
                toPlanRoute = true;
        }else{
            if (ImGui::Button("删除道路",ButtonSize))
                toDeleteObject = true;
        }
    }
    style.FramePadding = ImVec2(4.0f, 2.0f);
    style.ItemSpacing = ImVec2(8.0f, 4.0f);
    ImGui::PopFont();
}
}
