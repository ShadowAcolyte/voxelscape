#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "input.h"
#include "../camera.h"
#include "../config.h"

static bool __mouse_captured = true;
static float __lastx, __lasty;
static float __yaw, __pitch;

void input::init_mouse_input()
{
    __lastx = config::screen_width  / 2.0f;
    __lasty = config::screen_height / 2.0f;
    __yaw = __pitch = 0;
}

void input::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    // Prevents camera from making a sudden jump whenever window comes into focus
    if (__mouse_captured)
    {
        __lastx = xpos;
        __lasty = ypos;
        __mouse_captured = false;
        return;
    }
    float xoffset = config::mouse_sensitivity * (xpos - __lastx);
    float yoffset = config::mouse_sensitivity * (__lasty - ypos);
    __lastx = xpos;
    __lasty = ypos;
    __yaw += xoffset;
    __pitch += yoffset;
    if (__pitch > 89.0f)
        __pitch = 89.0f;
    if (__pitch < -89.0f)
        __pitch = -89.0f;
}

void input::handle_mouse_input(Camera* cam)
{
    cam->yaw = __yaw;
    cam->pitch = __pitch;
}
