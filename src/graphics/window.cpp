#include <stdlib.h>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "window.h"
#include "../log.h"
#include "shader.h"
#include "../world/chunk/chunk.h"
#include "../world/block/block.h"
#include "../world/block/blockid.h"

void APIENTRY _gl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei length, const GLchar* message, const void* userParam)
{
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
        logger::info("[OpenGL] {}", message);
    else if (severity == GL_DEBUG_SEVERITY_MEDIUM || severity == GL_DEBUG_SEVERITY_LOW)
        logger::warn("[OpenGL] {}", message);
    else
        logger::error("[OpenGL] {}", message);
}

void _window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::create()
{
    this->width = 1280;
    this->height = 720;
    this->title = "Gaia's Path";

    // Initialize GLFW
    logger::info("Initializing GLFW...");
    if (!glfwInit())
    {
        logger::critical("Failed to initialize GLFW!");
        exit(-1);
    }
    // Create a windowed mode window and its OpenGL context
    logger::info("Creating window...");
    this->handle = glfwCreateWindow(this->width, this->height, this->title, NULL, NULL);
    if (!this->handle)
    {
        logger::critical("Failed to create Window!");
        glfwTerminate();
        exit(-1);
    }
    glfwSetWindowSizeCallback(this->handle, _window_size_callback);
    // Make the window's context current
    glfwMakeContextCurrent(this->handle);
    // Initialize GLAD
    logger::info("Initializing OpenGL loader...");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        logger::critical("Failed to intialize OpenGL function loader (GLAD)!");
        exit(-1);
    }
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(_gl_debug_callback, nullptr);
    logger::info("Initialization complete.");
}

void Window::loop()
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

    ShaderProgram basic = shader::create_program("shaders/basic.vert", "shaders/basic.frag", nullptr);
    ShaderProgram chunk_mesh_compute = shader::create_program(nullptr, nullptr, "shaders/chunk_mesh_generator.comp");

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
    glBufferData(GL_SHADER_STORAGE_BUFFER, CHUNK_VOLUME * sizeof(uint32_t), &chunk1.blocks[0], GL_STATIC_COPY);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(this->handle))
    {
        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader::enable(basic);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        shader::disable();
        // Swap front and back buffers
        glfwSwapBuffers(this->handle);

        // Poll for and process events
        glfwPollEvents();
    }
}

void Window::destroy()
{
    glfwTerminate();
}
