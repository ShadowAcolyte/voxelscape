#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../config.h"
#include "../graphics/camera.h"
#include "input.h"

static bool _mouseCaptured = true;
static float _lastx, _lasty;
static float _yaw, _pitch;

void Input::InitMouseInput()
{
    _lastx = Config::SCREEN_WIDTH / 2.0f;
    _lasty = Config::SCREEN_HEIGHT / 2.0f;
    _yaw = _pitch = 0;
}

void Input::CursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
    // Prevents camera from making a sudden jump whenever window comes into
    // focus
    if (_mouseCaptured)
    {
        _lastx = xpos;
        _lasty = ypos;
        _mouseCaptured = false;
        return;
    }
    float xoffset = Config::MOUSE_SENSITIVITY * (xpos - _lastx);
    float yoffset = Config::MOUSE_SENSITIVITY * (_lasty - ypos);
    _lastx = xpos;
    _lasty = ypos;
    _yaw += xoffset;
    _pitch += yoffset;
    if (_pitch > 89.0f)
        _pitch = 89.0f;
    if (_pitch < -89.0f)
        _pitch = -89.0f;
}

void Input::HandleMouseInput(Camera *cam)
{
    cam->yaw = _yaw;
    cam->pitch = _pitch;
}
