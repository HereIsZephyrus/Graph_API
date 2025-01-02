//
//  main.cpp
//  Graph_API
//
//  Created by ChanningTong on 12/26/24.
//

#include <gtest/gtest.h>
#include <benchmark/benchmark.h>
#include "graph_api.hpp"
#include "graph_engine.hpp"

static void Initialization(GLFWwindow *&window);
int main(int argc, char **argv) {
    if (argc > 1){
        std::string program_type = argv[1];
        if (program_type == "utest"){
            ::testing::InitGoogleTest(&argc, argv);
            return RUN_ALL_TESTS();
        }
    }
    using namespace transport;
    GLFWwindow *& window = WindowParas::getInstance().window;
    Initialization(window);
    
    Camera2D& camera = Camera2D::getView();
    WUSG::Graph<valueType> graph(87575);
    WUSG::CreateGraphFromFile("/Users/channingtong/Program/Graph_API/usa.txt", graph,true);
    citys = BuildVisualPoints(graph);
    roads = BuildVisualRoads(graph);
    camera.setExtent(citys->getExtent());
    std::cout<<graph.vertexCount()<<' '<<graph.edgeCount()<<std::endl;
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        roads->draw();
        citys->draw();
        gui::DrawBasic();
        processOperator(window,graph);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void Initialization(GLFWwindow *& window){
    if (!HAS_INIT_OPENGL_CONTEXT && initOpenGL(window,"2025Autumn数据结构课设-交通管理系统") != 0){
        std::cout<<"init OpenGL failed"<<std::endl;
        return;
    }
    srand((unsigned int)time(NULL));
    InitResource(window);
    gui::Initialization(window);
    BufferRecorder& buffer = BufferRecorder::getBuffer();
    buffer.initIO(window);
}
