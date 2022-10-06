#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window();
    ~Window();

    GLFWwindow* m_handle;
    int m_width, m_height;
    std::string m_title;
};
