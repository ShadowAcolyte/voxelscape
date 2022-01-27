#ifndef GAIA_CHUNK_H
#define GAIA_CHUNK_H

#include <glm/vec3.hpp>
#include <vector>
#include <stdexcept>

#include "../block/block.h"
#include "chunk_constants.h"
#include "../../log.h"

struct Chunk
{
    std::vector<block::Block> blocks;
    glm::ivec3 position;

    Chunk(int x, int y, int z);

    inline block::Block& get_block(size_t x, size_t y, size_t z) noexcept
    {
        if (x < 0 || x > CHUNK_SIZE - 1 ||
            y < 0 || y > CHUNK_SIZE - 1 ||
            z < 0 || z > CHUNK_SIZE - 1)
        {
            logger::error("'std::vector<block::Block> blocks' in Chunk.h -> index out of bound!");
            exit(-1);
        }
        return blocks[y * CHUNK_AREA + z * CHUNK_SIZE + x];
    }

    void place_block(block::Block b, size_t x, size_t y, size_t z);
    void destroy_block(size_t x, size_t y, size_t z);
    void destroy_chunk();
};

#endif
