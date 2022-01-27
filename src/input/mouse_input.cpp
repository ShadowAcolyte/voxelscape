#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "input.h"
#include "../graphics/camera.h"
#include "../config.h"

static bool _mouse_captured = true;
static float _lastx, _lasty;
static float _yaw, _pitch;

void input::init_mouse_input()
{
    _lastx = config::screen_width / 2.0f;
    _lasty = config::screen_height / 2.0f;
    _yaw = _pitch = 0;
}

void input::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    // Prevents camera from making a sudden jump whenever window comes into focus
    if (_mouse_captured)
    {
        _lastx = xpos;
        _lasty = ypos;
        _mouse_captured = false;
        return;
    }
    float xoffset = config::mouse_senstivity * (xpos - _lastx);
    float yoffset = config::mouse_senstivity * (_lasty - ypos);
    _lastx = xpos;
    _lasty = ypos;
    _yaw += xoffset;
    _pitch += yoffset;
    if (_pitch > 89.0f)
        _pitch = 89.0f;
    if (_pitch < -89.0f)
        _pitch = -89.0f;
}

void input::handle_mouse_input(camera::Camera& cam)
{
    cam.yaw = _yaw;
    cam.pitch = _pitch;
}
