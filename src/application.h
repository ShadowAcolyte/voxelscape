#pragma once

#include "window.h"
#include "camera.h"
#include "shader.h"

class Application
{
public:
    Application();
    ~Application();

    void update(float delta_ms);
    void render();

    void run();
private:
    Window* window;
    Shader* basic_shader;
    Camera camera;

    const std::string VERSION = "0.3.0";
};
