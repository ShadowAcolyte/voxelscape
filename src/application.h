#pragma once

#include "graphics/camera.h"
#include "graphics/shader.h"
#include "graphics/window.h"

class Application
{
public:
    Application();
    ~Application();

    void Update(float delta_ms);
    void Render();

    void Run();

private:
    Window *window;
    Shader *basicShader;
    Camera camera;

    const std::string VERSION = "0.3.0";
};
