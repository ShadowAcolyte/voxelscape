#include <glad/glad.h>

#include "window.h"
#include "config.h"
#include "log.h"

void APIENTRY __gl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei length, const GLchar* message, const void* userParam) {
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
        logger::info("[OpenGL] {}", message);
    else if (severity == GL_DEBUG_SEVERITY_MEDIUM || severity == GL_DEBUG_SEVERITY_LOW)
        logger::warn("[OpenGL] {}", message);
    else
        logger::error("[OpenGL] {}", message);
}

Window::Window() {
    width  = config::screen_width;
    height = config::screen_height;
    title  = config::screen_title;

    // Initialize GLFW
    logger::info("Initializing GLFW...");
    if (!glfwInit()) {
        logger::critical("Failed to initialize GLFW!");
        exit(-1);
    }
    // Create a windowed mode window and its OpenGL context
    logger::info("Creating window...");
    handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!handle) {
        logger::critical("Failed to create Window!");
        glfwTerminate();
        exit(-1);
    }
    // Make the window's context current
    glfwMakeContextCurrent(handle);
    // Initialize GLAD
    logger::info("Initializing OpenGL loader...");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        logger::critical("Failed to intialize OpenGL function loader (GLAD)!");
        exit(-1);
    }
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(__gl_debug_callback, nullptr);
}

Window::~Window() {
    glfwTerminate();
}
