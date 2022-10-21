#include "application.h"

#include <glad/glad.h>

#include <glm/trigonometric.hpp>
#include <iostream>

#include "config.h"
#include "graphics/mesh.h"
#include "input/input.h"
#include "log.h"
#include "world/block.h"

static Camera *camptr;
static void s_WindowSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    camptr->Update(camptr->fov, width * 1.0f / height, 0.01f, 100.0f);
}

Application::Application()
    : camera(glm::radians(Config::FOV), Config::SCREEN_WIDTH * 1.0f / Config::SCREEN_HEIGHT, 0.01f, 100.0f)
{
    Logger::Init();
    window = new Window();
    basicShader = new Shader("shaders/basic.vert", "shaders/basic.frag");
    // set camera pointer for window resizing
    camptr = &camera;
    glfwSetWindowSizeCallback(window->handle, s_WindowSizeCallback);
    // Input handling
    Input::InitMouseInput();
    glfwSetCursorPosCallback(window->handle, Input::CursorPosCallback);
    glfwSetKeyCallback(window->handle, Input::KeyCallback);
    glfwSetInputMode(window->handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Logger::Info("Initialization complete.");
    Logger::Info("OpenGL version: {}", glGetString(GL_VERSION));
    Logger::Info("Voxelscape version: {}", VERSION);
}

Application::~Application()
{
    Logger::Info("Application stopped.");
}

void Application::Update(float delta_ms)
{
    Input::HandleMouseInput(&camera);
    Input::HandleKeyboardInput(delta_ms, &camera);
    camera.Update();
}

void Application::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    basicShader->Enable();
    basicShader->SetViewProj(camera.projView);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Application::Run()
{
    // time stuff
    int64_t previous_frame =
        std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch())
            .count();
    int64_t current_frame =
        std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch())
            .count();
    int64_t delta_ns;

    unsigned int _vao, _vbo;

    // temp stuff
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    float _data[] = {0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1};
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_data), _data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // debugging stuff
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glfwSwapInterval(0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!glfwWindowShouldClose(window->handle))
    {
        current_frame =
            std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch())
                .count();
        delta_ns = current_frame - previous_frame;
        previous_frame = current_frame;

        std::cout << "Last frame: " << delta_ns / 1000000.0f << "ms\tFrame rate: " << 1000000000.0f / delta_ns << '\r';

        // delta time in milliseconds
        Update(delta_ns / 1000000.0f);
        Render();

        glfwSwapBuffers(window->handle);
        glfwPollEvents();
    }
}
