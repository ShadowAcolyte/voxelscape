#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <map>
#include <queue>

#include "input.h"
#include "../camera.h"

struct __KeyEvent
{
    int key, scancode, action, mods;
    __KeyEvent(int key, int scancode, int action, int mods)
        : key(key), scancode(scancode), action(action), mods(mods) {}
};

static std::map<int, bool> __keys;
static std::queue<__KeyEvent> __unhandled_keys;

void input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    __unhandled_keys.emplace(key, scancode, action, mods);
}

void input::handle_keyboard_input(float delta, Camera* cam)
{
    while (!__unhandled_keys.empty())
    {
        __KeyEvent event = __unhandled_keys.front();
        __unhandled_keys.pop();
        bool pressed = event.action == GLFW_PRESS || event.action == GLFW_REPEAT;
        __keys[event.key] = pressed;
    }

    // Camera movement
    glm::vec3 movedir(0.0f, 0.0f, 0.0f);
    if (__keys[GLFW_KEY_W])
        movedir += glm::normalize(glm::vec3(cam->direction.x, 0.0f, cam->direction.z));
    if (__keys[GLFW_KEY_S])
        movedir -= glm::normalize(glm::vec3(cam->direction.x, 0.0f, cam->direction.z));
    if (__keys[GLFW_KEY_D])
        movedir += glm::normalize(glm::cross(cam->direction, Camera::up));
    if (__keys[GLFW_KEY_A])
        movedir -= glm::normalize(glm::cross(cam->direction, Camera::up));
    // Creative mode style vertical movement
    if (__keys[GLFW_KEY_SPACE])
        movedir.y += 1.0f;
    if (__keys[GLFW_KEY_LEFT_SHIFT])
        movedir.y -= 1.0f;
    if (glm::length(movedir) != 0)
        movedir = glm::normalize(movedir);

    cam->position += delta * cam->camspeed * movedir;
}
