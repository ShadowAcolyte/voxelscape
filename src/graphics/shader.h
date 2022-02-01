#ifndef VOX_SHADER_H
#define VOX_SHADER_H

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "../util/log.h"

class Shader
{
public:
    Shader(const char* vert_path, const char* frag_path, const char* comp_path);

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

#endif // !VOX_SHADER_H
