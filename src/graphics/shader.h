#ifndef VOX_SHADER_H
#define VOX_SHADER_H

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "../util/log.h"

namespace shader
{
    constexpr int UNIFORM_PROJ_VIEW_LOC = 0;

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

    inline void set_proj_view(const glm::mat4& proj_view) {
        glUniformMatrix4fv(UNIFORM_PROJ_VIEW_LOC, 1, GL_FALSE, & proj_view[0][0]);
    }
}

#endif // !VOX_SHADER_H
