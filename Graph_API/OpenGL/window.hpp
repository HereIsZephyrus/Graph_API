//
//  window.hpp
//  data_structure
//
//  Created by ChanningTong on 10/21/24.
//

#ifndef window_hpp
#define window_hpp

#include <cstring>
#include <string>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "graphing.hpp"

inline bool HAS_INIT_OPENGL_CONTEXT = false;
int initOpenGL(GLFWwindow *&window,std::string windowName);
int initImGUI(GLFWwindow* window);
class WindowParas{
public:
    static WindowParas& getInstance(){
        static WindowParas instance;
        return instance;
    }
    WindowParas(const WindowParas&) = delete;
    void operator=(const WindowParas&) = delete;
    GLFWwindow * window;
    const GLint WINDOW_WIDTH = 960;
    const GLint WINDOW_HEIGHT = 720;
    const GLint SIDEBAR_WIDTH = 200;
    GLint SCREEN_WIDTH,SCREEN_HEIGHT;
    GLfloat xScale,yScale;
    GLfloat defaultAlpha;
    bool mainWindowFocused;
    GLfloat screen2normalX(GLdouble screenX);
    GLfloat screen2normalY(GLdouble screenY);
    GLfloat normal2orthoX(GLfloat normalX);
    GLfloat normal2orthoY(GLfloat normalY);
private:
    WindowParas() {}
};

namespace maze {
using matrix = std::vector<std::vector<bool>>;
void DrawBasicWindow(GLFWwindow *&window,const Primitive& boundary);
}
#endif /* window_hpp */
