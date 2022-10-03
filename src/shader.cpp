#include <glad/glad.h>
#include <sstream>
#include <fstream>

#include "shader.h"

static int __check_compile_errors(unsigned int shader) {
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* info = new char[length];
        glGetShaderInfoLog(shader, length, NULL, info);
        logger::error("Shader compilation failed! \n {}", info);
        delete[] info;
    }
    return success;
}

static unsigned int __compile_shader(const std::string& type, const std::string& path) {
    std::ifstream file(path);
    std::string code;

    if (file.fail()) {
        logger::error("Failed to read shader file: '{}'!", path.c_str());
        return 0;
    }
    else {
        std::stringstream ss;
        ss << file.rdbuf();
        file.close();
        code = ss.str();
    }

    logger::info("Compiling shader '{}' of type '{}'.", path.c_str(), type.c_str());
    unsigned int shader = 0;
    const char* _code = code.c_str();

    if (type == "vertex")           shader = glCreateShader(GL_VERTEX_SHADER);
    else if (type == "fragment")    shader = glCreateShader(GL_FRAGMENT_SHADER);
    else if (type == "compute")     shader = glCreateShader(GL_COMPUTE_SHADER);
    else {
        logger::error("Unknow shader type passed in __compile_shader(): '{}'!", type.c_str());
        return 0;
    }

    glShaderSource(shader, 1, &_code, NULL);
    glCompileShader(shader);
    if (__check_compile_errors(shader) != GL_TRUE)
        return 0;
    return shader;
}

static int __check_link_errors(unsigned int program) {
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success != GL_TRUE) {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char* info = new char[length];
        glGetProgramInfoLog(program, length, NULL, info);
        logger::error("Shader program linking error!\n{}", 1, info);
        delete[] info;
    }
    return success;
}

Shader::Shader(const char* vert_path, const char* frag_path, const char* comp_path) {
    unsigned int vs, fs, cs;
    vs = fs = cs = 0;
    if (vert_path != nullptr) {
        vs = __compile_shader("vertex", vert_path);
        if (!vs) {
            id = 0;
            std::exit(-1);
        }
    }
    if (frag_path != nullptr) {
        fs = __compile_shader("fragment", frag_path);
        if (!fs) {
            id = 0;
            std::exit(-1);
        }
    }
    if (comp_path != nullptr) {
        cs = __compile_shader("compute", comp_path);
        if (!cs) {
            id = 0;
            std::exit(-1);
        }
    }

    id = glCreateProgram();
    logger::info("Creating shader program. (id {})", id);
    if (vs)  glAttachShader(id, vs);
    if (fs)  glAttachShader(id, fs);
    if (cs)  glAttachShader(id, cs);
    glLinkProgram(id);

    if (__check_link_errors(id) != GL_TRUE) {
        glDeleteProgram(id);
        std::exit(-1);
    }
}
