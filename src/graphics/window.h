#ifndef GAIA_WINDOW_H
#define GAIA_WINDOW_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

struct Window
{
    GLFWwindow* handle;
    int width, height;
    const char* title;

    void create();
    void destroy();
};

#endif // GAIA_WINDOW_H
