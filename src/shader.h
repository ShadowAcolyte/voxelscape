#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "log.h"

class Shader {
public:
    Shader(const char* vert_path, const char* frag_path, const char* comp_path);

    inline void enable() {
        if (!id) {
            logger::warn("Cannot use program, program ID is 0!");
            return;
        }
        glUseProgram(id);
    }

    inline void destroy() {
        glDeleteProgram(id);
    }

    inline void set_view_proj(const glm::mat4& viewProj) {
        glUniformMatrix4fv(0, 1, GL_FALSE, &viewProj[0][0]);
    }

private:
    unsigned int id = 0;
};
