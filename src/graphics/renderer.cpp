#include <glad/glad.h>

#include "renderer.h"
#include "../world/chunk/chunk.h"

static float _face_vert_table[] = {
            0, 0, 0, 1,     // no direction
            0, 0, 0, 1,
            0, 0, 0, 1,
            0, 0, 0, 1,
            0, 0, 0, 1,
            0, 0, 0, 1,
            // north
            1, 1, 0, 1,
            1, 0, 0, 1,
            0, 0, 0, 1,
            0, 0, 0, 1,
            0, 1, 0, 1,
            1, 1, 0, 1,
            // south
            0, 1, 1, 1,
            0, 0, 1, 1,
            1, 0, 1, 1,
            1, 0, 1, 1,
            1, 1, 1, 1,
            0, 1, 1, 1,
            // east
            1, 1, 1, 1,
            1, 0, 1, 1,
            1, 0, 0, 1,
            1, 0, 0, 1,
            1, 1, 0, 1,
            1, 1, 1, 1,
            // west
            0, 1, 0, 1,
            0, 0, 0, 1,
            0, 0, 1, 1,
            0, 0, 1, 1,
            0, 1, 1, 1,
            0, 1, 0, 1,
            // top
            0, 1, 0, 1,
            0, 1, 1, 1,
            1, 1, 1, 1,
            1, 1, 1, 1,
            1, 1, 0, 1,
            0, 1, 0, 1,
            // bottom
            1, 0, 0, 1,
            1, 0, 1, 1,
            0, 0, 1, 1,
            0, 0, 1, 1,
            0, 0, 0, 1,
            1, 0, 0, 1,
};

void renderer::render_chunk(const Chunk* chunk)
{

}