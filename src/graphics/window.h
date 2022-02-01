#ifndef VOX_WINDOW_H
#define VOX_WINDOW_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

struct Window
{
    GLFWwindow* m_handle;
    int m_width, m_height;
    const char* m_title;

    void Create();
    void Destroy();
};

#endif // !VOX_WINDOW_H
