#include <glad/glad.h>
#include <sstream>
#include <fstream>

#include "shader.h"

static int _check_compile_errors(unsigned int shader)
{
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* info = new char[length];
        glGetShaderInfoLog(shader, length, NULL, info);
        logger::error("Shader compilation failed! \n %s", 1, info);
        delete[] info;
    }
    return success;
}

static unsigned int _compile_shader(const std::string& type, const std::string& path)
{
    std::ifstream file(path);
    std::string code;

    if (file.fail())
    {
        logger::error("Failed to read shader file: %s!", 1, path.c_str());
        return 0;
    }
    else
    {
        std::stringstream ss;
        ss << file.rdbuf();
        file.close();
        code = ss.str();
    }

    logger::info("Compiling shader %s of type %s.", 2, path.c_str(), type.c_str());
    unsigned int shader = NULL;
    const char* _code = code.c_str();

    if (type == "VERTEX")           shader = glCreateShader(GL_VERTEX_SHADER);
    else if (type == "FRAGMENT")    shader = glCreateShader(GL_FRAGMENT_SHADER);
    else if (type == "COMPUTE")     shader = glCreateShader(GL_COMPUTE_SHADER);
    else
    {
        logger::error("Unknow shader type passed in _compile_shader(): %s!", 1, type.c_str());
        return 0;
    }

    glShaderSource(shader, 1, &_code, NULL);
    glCompileShader(shader);
    if (_check_compile_errors(shader) != GL_TRUE)
        return 0;
    return shader;
}

static int _check_link_errors(ShaderProgram program)
{
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success != GL_TRUE)
    {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char* info = new char[length];
        glGetProgramInfoLog(program, length, NULL, info);
        logger::error("Shader program linking error!\n%s", 1, info);
        delete[] info;
    }
    return success;
}

ShaderProgram shader::create_program(const char* vert_path, const char* frag_path, const char* comp_path)
{
    unsigned int vs, fs, cs;
    vs = fs = cs = 0;
    if (vert_path != nullptr) {
        vs = _compile_shader("VERTEX", vert_path);
        if (!vs)
            return 0;
    }
    if (frag_path != nullptr) {
        fs = _compile_shader("FRAGMENT", frag_path);
        if (!fs)
            return 0;
    }
    if (comp_path != nullptr) {
        cs = _compile_shader("COMPUTE", comp_path);
        if (!cs)
            return 0;
    }

    logger::info("Creating shader program.");
    ShaderProgram program = glCreateProgram();
    if (vs)  glAttachShader(program, vs);
    if (fs)  glAttachShader(program, fs);
    if (cs)  glAttachShader(program, cs);
    glLinkProgram(program);

    if (_check_link_errors(program) != GL_TRUE)
        return 0;
    return program;
}
