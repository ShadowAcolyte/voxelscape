#ifndef GAIA_SHADER_H
#define GAIA_SHADER_H

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "../util/log.h"

namespace shader
{
    typedef unsigned int ShaderProgram;
    ShaderProgram create_program(const char* vert_path, const char* frag_path, const char* comp_path);

    inline void enable(ShaderProgram id) {
        if (!id) {
            logger::warn("Cannot use program, program ID is 0!");
            return;
        }
        glUseProgram(id);
    }

    inline void disable() {
        glUseProgram(0);
    }

    inline void destroy(ShaderProgram id) {
        glDeleteProgram(id);
    }

    inline void set_uniformb(const ShaderProgram shader, const std::string& name, bool value) {
        glUniform1i(glGetUniformLocation(shader, name.c_str()), value);
    }

    inline void set_uniform1i(const ShaderProgram shader, const std::string& name, int value) {
        glUniform1i(glGetUniformLocation(shader, name.c_str()), value);
    }

    inline void set_uniform1f(const ShaderProgram shader, const std::string& name, float value) {
        glUniform1f(glGetUniformLocation(shader, name.c_str()), value);
    }

    inline void set_uniform2fv(const ShaderProgram shader, const std::string& name, const glm::vec2& value) {
        glUniform2fv(glGetUniformLocation(shader, name.c_str()), 1, &value[0]);
    }

    inline void set_uniform3fv(const ShaderProgram shader, const std::string& name, const glm::vec3& value) {
        glUniform3fv(glGetUniformLocation(shader, name.c_str()), 1, &value[0]);
    }

    inline void set_uniform4fv(const ShaderProgram shader, const std::string& name, const glm::vec4& value) {
        glUniform4fv(glGetUniformLocation(shader, name.c_str()), 1, &value[0]);
    }

    inline void set_uniformMat2fv(const ShaderProgram shader, const std::string& name, const glm::mat2& mat) {
        glUniformMatrix2fv(glGetUniformLocation(shader, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    inline void set_unfiromMat3fv(const ShaderProgram shader, const std::string& name, const glm::mat3& mat) {
        glUniformMatrix3fv(glGetUniformLocation(shader, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    inline void set_uniformMat4fv(const ShaderProgram shader, const std::string& name, const glm::mat4& mat) {
        glUniformMatrix4fv(glGetUniformLocation(shader, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
}

#endif // GAIA_SHADER_H
