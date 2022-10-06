#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "log.h"

class Shader
{
public:
    Shader(const std::string& vert_path, const std::string& frag_path, const std::string& comp_path = "");

    inline void Enable() {
        if (!m_id) {
            Logger::Warn("Cannot use program, program ID is 0!");
            return;
        }
        glUseProgram(m_id);
    }

    inline void Destroy() {
        glDeleteProgram(m_id);
    }

    inline void SetViewProj(const glm::mat4& viewProj) {
        glUniformMatrix4fv(0, 1, GL_FALSE, &viewProj[0][0]);
    }

private:
    unsigned int m_id = 0;
};
