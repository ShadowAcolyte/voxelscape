#include <glad/glad.h>
#include <glm/trigonometric.hpp>

#include <iostream>

#include "application.h"
#include "config.h"
#include "log.h"
#include "input/input.h"

static Camera* camptr;
static void __window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    camptr->update(camptr->fov, width * 1.0f / height, 0.01f, 100.0f);
}

Application::Application()
    :  camera(glm::radians(config::fov), config::screen_width * 1.0f / config::screen_width, 0.1f, 100.0f)
{
    logger::init();
    window = new Window();
    basic_shader = new Shader("shaders/basic.vert", "shaders/basic.frag", nullptr);
    // set camera pointer for window resizing
    camptr = &camera;
    glfwSetWindowSizeCallback(window->handle, __window_size_callback);
    // Input handling
    input::init_mouse_input();
    glfwSetCursorPosCallback(window->handle, input::cursor_pos_callback);
    glfwSetKeyCallback(window->handle, input::key_callback);
    glfwSetInputMode(window->handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    logger::info("Initialization complete.");
    logger::info("OpenGL version: {}", glGetString(GL_VERSION));
    logger::info("Voxelscape version: {}", VERSION);
}

Application::~Application()
{
    logger::info("Application stopped.");
}

void Application::update(float delta_ms)
{
    input::handle_mouse_input(&camera);
    input::handle_keyboard_input(delta_ms, &camera);
    camera.update();
}

unsigned int _vao, _vbo;

void Application::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    basic_shader->enable();
    basic_shader->set_view_proj(camera.proj_view);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Application::run()
{
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

    glfwSwapInterval(0);
    glClearColor(1.0f, 0.7f, 0.1f, 1.0f);
    while (!glfwWindowShouldClose(window->handle))
    {
        current_frame = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        delta_ns = current_frame - previous_frame;
        previous_frame = current_frame;

        // delta time in milliseconds
        update(delta_ns / 1000000.0f);
        render();

        glfwSwapBuffers(window->handle);
        glfwPollEvents();
    }
}
