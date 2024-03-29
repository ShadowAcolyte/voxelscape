#include <fstream>
#include <glad/glad.h>
#include <sstream>

#include "shader.h"

static int s_CheckCompileErrors(unsigned int shader)
{
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char *Info = new char[length];
        glGetShaderInfoLog(shader, length, NULL, Info);
        Logger::Error("Shader compilation failed! \n {}", Info);
        delete[] Info;
    }
    return success;
}

static unsigned int s_CompileShader(const std::string &type, const std::string &path)
{
    std::ifstream file(path);
    std::string code;

    if (file.fail())
    {
        Logger::Error("Failed to read shader file: '{}'!", path.c_str());
        return 0;
    }
    else
    {
        std::stringstream ss;
        ss << file.rdbuf();
        file.close();
        code = ss.str();
    }

    Logger::Info("Compiling shader '{}' of type '{}'.", path.c_str(), type.c_str());
    unsigned int shader = 0;
    const char *_code = code.c_str();

    if (type == "vertex")
        shader = glCreateShader(GL_VERTEX_SHADER);
    else if (type == "fragment")
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    else if (type == "compute")
        shader = glCreateShader(GL_COMPUTE_SHADER);
    else
    {
        Logger::Error("Unknow shader type passed in _CompileShader(): '{}'!", type.c_str());
        return 0;
    }

    glShaderSource(shader, 1, &_code, NULL);
    glCompileShader(shader);
    if (s_CheckCompileErrors(shader) != GL_TRUE)
        return 0;
    return shader;
}

static int s_CheckLinkErrors(unsigned int program)
{
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success != GL_TRUE)
    {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char *Info = new char[length];
        glGetProgramInfoLog(program, length, NULL, Info);
        Logger::Error("Shader program linking error!\n{}", 1, Info);
        delete[] Info;
    }
    return success;
}

Shader::Shader(const std::string &vert_path, const std::string &frag_path, const std::string &comp_path)
{
    unsigned int vs, fs, cs;
    vs = fs = cs = 0;
    if (!vert_path.empty())
    {
        vs = s_CompileShader("vertex", vert_path);
        if (!vs)
        {
            id = 0;
            std::exit(-1);
        }
    }
    if (!frag_path.empty())
    {
        fs = s_CompileShader("fragment", frag_path);
        if (!fs)
        {
            id = 0;
            std::exit(-1);
        }
    }
    if (!comp_path.empty())
    {
        cs = s_CompileShader("compute", comp_path);
        if (!cs)
        {
            id = 0;
            std::exit(-1);
        }
    }

    id = glCreateProgram();
    Logger::Info("Creating shader program. (id {})", id);
    if (vs)
        glAttachShader(id, vs);
    if (fs)
        glAttachShader(id, fs);
    if (cs)
        glAttachShader(id, cs);
    glLinkProgram(id);

    if (s_CheckLinkErrors(id) != GL_TRUE)
    {
        glDeleteProgram(id);
        std::exit(-1);
    }
}
