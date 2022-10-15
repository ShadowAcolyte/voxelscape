#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <map>
#include <queue>

#include "input.h"
#include "../graphics/camera.h"

struct KeyEvent {
    int key, scancode, action, mods;
    KeyEvent(int key, int scancode, int action, int mods)
        : key(key), scancode(scancode), action(action), mods(mods) {}
};

static std::map<int, bool> _keys;
static std::queue<KeyEvent> _unhandledKeys;

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    _unhandledKeys.emplace(key, scancode, action, mods);
}

void Input::HandleKeyboardInput(float delta, Camera* cam)
{
    while (!_unhandledKeys.empty())
    {
        KeyEvent event = _unhandledKeys.front();
        _unhandledKeys.pop();
        bool pressed = event.action == GLFW_PRESS || event.action == GLFW_REPEAT;
        _keys[event.key] = pressed;
    }

    // Camera movement
    glm::vec3 movedir(0.0f, 0.0f, 0.0f);
    if (_keys[GLFW_KEY_W])
        movedir += glm::normalize(glm::vec3(cam->m_direction.x, 0.0f, cam->m_direction.z));
    if (_keys[GLFW_KEY_S])
        movedir -= glm::normalize(glm::vec3(cam->m_direction.x, 0.0f, cam->m_direction.z));
    if (_keys[GLFW_KEY_D])
        movedir += glm::normalize(glm::cross(cam->m_direction, Camera::up));
    if (_keys[GLFW_KEY_A])
        movedir -= glm::normalize(glm::cross(cam->m_direction, Camera::up));
    // Creative mode style vertical movement
    if (_keys[GLFW_KEY_SPACE])
        movedir.y += 1.0f;
    if (_keys[GLFW_KEY_LEFT_SHIFT])
        movedir.y -= 1.0f;
    if (glm::length(movedir) != 0)
        movedir = glm::normalize(movedir);

    cam->m_position += delta * cam->m_camspeed * movedir;
}
