#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <stb_image.h>
#include <glm/trigonometric.hpp>
#include <sstream>

#include "config.h"
#include "util/log.h"
#include "util/timer.h"
#include "input/input.h"
#include "graphics/window.h"
#include "graphics/camera.h"
#include "graphics/shader.h"
#include "world/chunk/chunk.h"
#include <iostream>

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
        logger::info("------------------------VOXELSCAPE LOG BEGIN------------------------");
        window.create();
        glfwSetWindowSizeCallback(window.handle, _window_size_callback);
        // Input handling
        input::init_mouse_input();
        glfwSetCursorPosCallback(window.handle, input::cursor_pos_callback);
        glfwSetKeyCallback(window.handle, input::key_callback);
        glfwSetInputMode(window.handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        logger::info("Initialization complete.");
        logger::info("{}", glGetString(GL_VERSION));
    }

    static void run()
    {
        shader::ShaderProgram basic = shader::create_program("shaders/basic.vert", "shaders/basic.frag", nullptr);
        shader::ShaderProgram chunk_mesh_compute_shader = shader::create_program(nullptr, nullptr, "shaders/chunk_mesh_generator.comp");
        shader::ShaderProgram chunk_shader = shader::create_program("shaders/chunk_shader.vert", "shaders/chunk_shader.frag", nullptr);
        cam = camera::Camera(glm::radians(config::fov), window.width * 1.0f / window.height, 0.1f, 100.0f);

        int width, height, channels;
        unsigned char* data = stbi_load("textures/block.jpg", &width, &height, &channels, 0);
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
                    if ((x * x + y * y + z * z) <= 16 * 16)
                        chunk1.place_block(block::create(blockid::GRASS), x, y, z);
                }
            }
        }

        //for (int x = 0; x < CHUNK_SIZE; x++)
        //    chunk1.place_block(block::create(blockid::GRASS), x, 0, 0);
        //for (int y = 0; y < CHUNK_SIZE; y++)
        //    chunk1.place_block(block::create(blockid::GRASS), 0, y, 0);
        //for (int z = 0; z < CHUNK_SIZE; z++)
        //    chunk1.place_block(block::create(blockid::GRASS), 0, 0, z);

        //float buffer_data[] = {
        //    0.0f, 0.0f, 0.0f,
        //    1.0f, 0.0f, 0.0f,
        //    1.0f, 1.0f, 0.0f,
        //    1.0f, 1.0f, 0.0f,
        //    0.0f, 1.0f, 0.0f,
        //    0.0f, 0.0f, 0.0f
        //};
        //
        //float buffer_data2[] = {
        //    0.0f, 0.0f, 0.0f,
        //    2.0f, 0.0f, 0.0f,
        //    2.0f, 1.0f, 0.0f,
        //    2.0f, 1.0f, 0.0f,
        //    0.0f, 1.0f, 0.0f,
        //    0.0f, 0.0f, 0.0f
        //};

        //testing
        uint32_t face_data[24576]{ 0 };
        uint32_t atomic_count = 0;

        unsigned int ssbo1, ssbo2;
        glGenBuffers(1, &ssbo1);
        glGenBuffers(1, &ssbo2);

        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo1);
        glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(block::Block) * CHUNK_VOLUME, &chunk1.blocks[0], GL_STATIC_READ);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo1);

        //uint32_t face_data[] = {
        //    //0x1, 0x2, 0x3, 0x4
        //    //0b0001, 0b1001, 0b10001
        //    0x1, 0X2, 0X3, 0X4, 0X5, 0X6,
        //    0x11, 0x12, 0x13, 0x14, 0x15, 0x16
        //};
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo2);
        glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(block::Block) * CHUNK_VOLUME * 6, NULL, GL_DYNAMIC_DRAW);
        //glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(face_data), face_data, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbo2);

        unsigned int indirect_buffer;
        glGenBuffers(1, &indirect_buffer);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, indirect_buffer);
        uint32_t indirect_data[] = {0, 1, 0, 0};
        glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(indirect_data), indirect_data, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, indirect_buffer);
        glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirect_buffer);

        unsigned int ssbo_face_vert_table;
        glGenBuffers(1, &ssbo_face_vert_table);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo_face_vert_table);
        float table_data[] = {
            0, 0, 0, 1,     // no direction
            0, 0, 0, 1,
            0, 0, 0, 1,
            0, 0, 0, 1,
            0, 0, 0, 1,
            0, 0, 0, 1,
            // north
            1, 1, 0, 1,
            1, 0, 0, 1,
            0, 0, 0, 1,
            0, 0, 0, 1,
            0, 1, 0, 1,
            1, 1, 0, 1,
            // south
            0, 1, 1, 1,
            0, 0, 1, 1,
            1, 0, 1, 1,
            1, 0, 1, 1,
            1, 1, 1, 1,
            0, 1, 1, 1,
            // east
            1, 1, 1, 1,
            1, 0, 1, 1,
            1, 0, 0, 1,
            1, 0, 0, 1,
            1, 1, 0, 1,
            1, 1, 1, 1,
            // west
            0, 1, 0, 1,
            0, 0, 0, 1,
            0, 0, 1, 1,
            0, 0, 1, 1,
            0, 1, 1, 1,
            0, 1, 0, 1,
            // top
            0, 1, 0, 1,
            0, 1, 1, 1,
            1, 1, 1, 1,
            1, 1, 1, 1,
            1, 1, 0, 1,
            0, 1, 0, 1,
            // bottom
            1, 0, 0, 1,
            1, 0, 1, 1,
            0, 0, 1, 1,
            0, 0, 1, 1,
            0, 0, 0, 1,
            1, 0, 0, 1,
        };
        glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(table_data), table_data, GL_STATIC_READ);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, ssbo_face_vert_table);

        unsigned int atomic_buffer;
        glGenBuffers(1, &atomic_buffer);
        glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, atomic_buffer);
        glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(unsigned int), NULL, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, atomic_buffer);

        unsigned int vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        float vertices[] = {
            1, 1, 1,
            1, 0, 1,
            0, 0, 1,
            0, 0, 1,
            0, 1, 1,
            1, 1, 1
        };
        unsigned int vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_READ);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
        glEnable(GL_DEPTH_TEST);
        glfwSwapInterval(0);    // turn off vsync
        std::stringstream _title;
        _title.setf(std::ios::fixed, std::ios::floatfield);
        _title.precision(3);
        while (!glfwWindowShouldClose(window.handle))
        {
            input::handle_mouse_input(cam);
            input::handle_keyboard_input(timer::get_delta_ms(), cam);
            camera::update(cam);

            _title << "Voxelscape - FPS: " << timer::get_fps_avg() << ", Frame Time : " << timer::get_delta_ms_avg() << " ms";
            glfwSetWindowTitle(window.handle, _title.str().c_str());
            _title.str("");

            //glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(indirect_data), indirect_data, GL_DYNAMIC_DRAW);
            glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(unsigned int), NULL, GL_DYNAMIC_DRAW);
            shader::enable(chunk_mesh_compute_shader);
            glDispatchCompute(2, 2, 2);
            shader::disable();
            glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

            //glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo2);
            //glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(uint32_t)* CHUNK_VOLUME * 6, face_data);
            //glGetBufferSubData(GL_ATOMIC_COUNTER_BUFFER, 0, sizeof(uint32_t), &atomic_count);
            //glGetBufferSubData(GL_DRAW_INDIRECT_BUFFER, 0, 4 * sizeof(uint32_t), indirect_data);
            //for (int i = 0; i < 4; i++)
            //    std::cout << indirect_data[i] << '\n';

            shader::enable(chunk_shader);
            shader::set_proj_view(cam.proj_view);
            //glDrawArrays(GL_TRIANGLES, 0, 6 * 12);
            glDrawArraysIndirect(GL_TRIANGLES, 0);
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
        logger::info("------------------------VOXELSCAPE LOG END------------------------");
    }
}

int main()
{
    game::init();
    game::run();
    game::destroy();
    return 0;
}
