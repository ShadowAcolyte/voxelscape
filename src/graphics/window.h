#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
    Window();
    ~Window();

    GLFWwindow *handle;
    int width, height;
    std::string title;
};
