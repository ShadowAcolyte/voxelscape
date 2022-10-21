#include "window.h"

#include <glad/glad.h>

#include "../config.h"
#include "../log.h"

void APIENTRY s_glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam)
{
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
        Logger::Info("[OpenGL] {}", message);
    else if (severity == GL_DEBUG_SEVERITY_MEDIUM || severity == GL_DEBUG_SEVERITY_LOW)
        Logger::Warn("[OpenGL] {}", message);
    else
        Logger::Error("[OpenGL] {}", message);
}

Window::Window()
{
    width = Config::SCREEN_WIDTH;
    height = Config::SCREEN_HEIGHT;
    title = Config::SCREEN_TITLE;

    // Initialize GLFW
    Logger::Info("Initializing GLFW...");
    if (!glfwInit())
    {
        Logger::Critical("Failed to initialize GLFW!");
        exit(-1);
    }
    // Create a windowed mode window and its OpenGL context
    Logger::Info("Creating window...");
    handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!handle)
    {
        Logger::Critical("Failed to create Window!");
        glfwTerminate();
        exit(-1);
    }
    // Make the window's context current
    glfwMakeContextCurrent(handle);
    // Initialize GLAD
    Logger::Info("Initializing OpenGL loader...");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Logger::Critical("Failed to intialize OpenGL function loader (GLAD)!");
        exit(-1);
    }
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(s_glDebugCallback, nullptr);
    glViewport(0, 0, width, height);
}

Window::~Window()
{
    glfwTerminate();
}
