#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <stb_image.h>
#include <format>
#include <glm/trigonometric.hpp>

#include "config.h"
#include "util/log.h"
#include "util/timer.h"
#include "input/input.h"
#include "graphics/window.h"
#include "graphics/camera.h"
#include "graphics/shader.h"
#include "world/chunk/chunk.h"

static Window window;
static camera::Camera cam;

static void _window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    camera::update(cam, cam.fov, width * 1.0f / height, 0.01f, 100.0f);
}

namespace game
{
    static void init()
    {
        logger::init();
        logger::info("------------------------GAIA LOG BEGIN------------------------");
        window.create();
        glfwSetWindowSizeCallback(window.handle, _window_size_callback);
        // Input handling
        input::init_mouse_input();
        glfwSetCursorPosCallback(window.handle, input::cursor_pos_callback);
        glfwSetKeyCallback(window.handle, input::key_callback);
        glfwSetInputMode(window.handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        logger::info("Initialization complete.");
    }

    static void run()
    {
        float vertices[] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
        };
        unsigned int indices[] = {
            0, 1, 2, 2, 3, 0
        };

        unsigned int vao, vbo, ebo;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        shader::ShaderProgram basic = shader::create_program("shaders/basic.vert", "shaders/basic.frag", nullptr);
        shader::ShaderProgram chunk_mesh_compute_shader = shader::create_program(nullptr, nullptr, "shaders/chunk_mesh_generator.comp");
        cam = camera::Camera(glm::radians(config::fov), window.width * 1.0f / window.height, 0.1f, 100.0f);

        int width, height, channels;
        unsigned char* data = stbi_load("textures/wall.jpg", &width, &height, &channels, 0);
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);

        Chunk chunk1(0, 0, 0);
        for (int x = 0; x < CHUNK_SIZE; x++)
        {
            for (int y = 0; y < CHUNK_SIZE; y++)
            {
                for (int z = 0; z < CHUNK_SIZE; z++)
                {
                    chunk1.place_block(block::Block(blockid::GRASS), x, y, z);
                }
            }
        }

        unsigned int ssbo;
        glGenBuffers(1, &ssbo);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
        glBufferData(GL_SHADER_STORAGE_BUFFER, CHUNK_VOLUME * sizeof(block::Block), &chunk1.blocks[0], GL_DYNAMIC_READ);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

        unsigned int chunk_shader_output_buffer;
        glGenBuffers(1, &chunk_shader_output_buffer);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glfwSetTime(0);
        glfwSwapInterval(0);    // turn off vsync
        while (!glfwWindowShouldClose(window.handle))
        {
            input::handle_mouse_input(cam);
            input::handle_keyboard_input(timer::get_delta_ms(), cam);
            camera::update(cam);
            //sprintf(_title, "Voxelscape - FPS: %f, Frame Time: %f ms", timer::get_fps(), timer::get_delta_us());
            //glfwSetWindowTitle(window.handle, std::format("Voxelscape - FPS: {}, Frame Time: {} ms", timer::get_fps(), timer::get_delta_us()));
            //logger::info("Frame time: {}us, FPS: {}", timer::get_delta_us(), timer::get_fps());
            glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader::enable(chunk_mesh_compute_shader);
            glDispatchCompute(1, 1, 1);
            shader::disable();

            shader::enable(basic);
            shader::set_uniformMat4fv(basic, "proj_view", cam.proj_view);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            shader::disable();
            // Swap front and back buffers
            glfwSwapBuffers(window.handle);

            // Poll for and process events
            glfwPollEvents();
            timer::tick();
        }
    }

    static void destroy()
    {
        window.destroy();
    }
}

int main()
{
    game::init();
    game::run();
    game::destroy();
    return 0;
}
