#pragma once

#include "graphics/window.h"
#include "graphics/camera.h"
#include "graphics/shader.h"

class Application {
public:
    Application();
    ~Application();

    void Update(float delta_ms);
    void Render();

    void Run();
private:
    Window* m_window;
    Shader* m_basicShader;
    Camera m_camera;

    const std::string VERSION = "0.3.0";
};
