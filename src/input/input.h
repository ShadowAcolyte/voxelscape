#pragma once

struct GLFWwindow;
class Camera;

namespace Input {
    void InitMouseInput();
    void CursorPosCallback(GLFWwindow *window, double xpos, double ypos);
    void HandleMouseInput(Camera *cam);
    void KeyCallback(GLFWwindow *window, int key, int scancode, int action,
                     int mods);
    void HandleKeyboardInput(float delta, Camera *cam);
}  // namespace Input
