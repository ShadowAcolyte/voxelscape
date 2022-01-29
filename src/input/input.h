#ifndef VOX_INPUT_H
#define VOX_INPUT_H

struct GLFWwindow;
namespace camera { struct Camera; }

namespace input
{
    void init_mouse_input();
    void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
    void handle_mouse_input(camera::Camera& cam);
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void handle_keyboard_input(float delta, camera::Camera& cam);
}

#endif // !VOX_INPUT_H
