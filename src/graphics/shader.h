#ifndef GAIA_SHADER_H
#define GAIA_SHADER_H

#include <glad/glad.h>

#include "../log.h"

typedef unsigned int ShaderProgram;

namespace shader
{
    ShaderProgram create_program(const char* vert_path, const char* frag_path, const char* comp_path);

    inline void enable(ShaderProgram id)
    {
        if (!id)
        {
            logger::warn("Cannot use program, program ID is 0!");
            return;
        }
        glUseProgram(id);
    }

    inline void disable()
    {
        glUseProgram(0);
    }

    inline void destroy(ShaderProgram id)
    {
        glDeleteProgram(id);
    }
}

#endif // GAIA_SHADER_H
