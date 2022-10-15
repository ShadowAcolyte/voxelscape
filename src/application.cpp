#include <glad/glad.h>
#include <glm/trigonometric.hpp>

#include <iostream>

#include "application.h"
#include "config.h"
#include "log.h"
#include "graphics/mesh.h"
#include "input/input.h"

static Camera* camptr;
static void _WindowSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    camptr->Update(camptr->m_fov, width * 1.0f / height, 0.01f, 100.0f);
}

Application::Application()
    :  m_camera(glm::radians(Config::FOV), Config::SCREEN_WIDTH * 1.0f / Config::SCREEN_HEIGHT, 0.01f, 100.0f) {
    Logger::Init();
    m_window = new Window();
    m_basicShader = new Shader("shaders/basic.vert", "shaders/basic.frag");
    // set camera pointer for window resizing
    camptr = &m_camera;
    glfwSetWindowSizeCallback(m_window->m_handle, _WindowSizeCallback);
    // Input handling
    Input::InitMouseInput();
    glfwSetCursorPosCallback(m_window->m_handle, Input::CursorPosCallback);
    glfwSetKeyCallback(m_window->m_handle, Input::KeyCallback);
    glfwSetInputMode(m_window->m_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Logger::Info("Initialization complete.");
    Logger::Info("OpenGL version: {}", glGetString(GL_VERSION));
    Logger::Info("Voxelscape version: {}", VERSION);
}

Application::~Application() {
    Logger::Info("Application stopped.");
}

void Application::Update(float delta_ms) {
    Input::HandleMouseInput(&m_camera);
    Input::HandleKeyboardInput(delta_ms, &m_camera);
    m_camera.Update();
}

unsigned int _vao, _vbo;

void Application::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_basicShader->Enable();
    m_basicShader->SetViewProj(m_camera.m_projView);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Application::Run() {
    // time stuff
    int64_t previous_frame = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    int64_t current_frame = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    int64_t delta_ns;

    //temp stuff
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    float _data[] = {
        0, 0, 1,
        1, 0, 1,
        1, 1, 1,
        1, 1, 1,
        0, 1, 1,
        0, 0, 1
    };
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_data), _data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // debugging stuff
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glfwSwapInterval(0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!glfwWindowShouldClose(m_window->m_handle)) {
        current_frame = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        delta_ns = current_frame - previous_frame;
        previous_frame = current_frame;

        // delta time in milliseconds
        Update(delta_ns / 1000000.0f);
        Render();

        glfwSwapBuffers(m_window->m_handle);
        glfwPollEvents();
    }
}
