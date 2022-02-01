#ifndef VOX_CHUNK_H
#define VOX_CHUNK_H

#include <vector>
#include <glm/vec3.hpp>

#include "chunk_constants.h"
#include "../block/block.h"
#include "../../graphics/mesh.h"

class Chunk
{
public:
    std::vector<Block> m_blocks = std::vector<Block>(CHUNK_VOLUME, Block());
    glm::ivec3 m_position;
    Mesh m_mesh;

    Chunk(const glm::ivec3& position)
        : m_position(position) {}
    Chunk(unsigned int x, unsigned int y, unsigned int z)
        : m_position(x, y, z) {}

    inline Block* GetBlockPtr(size_t x, size_t y, size_t z)
    {
        return &m_blocks[x + y * CHUNK_AREA + z * CHUNK_SIZE];
    }

    void PlaceBlock(const Block& block, size_t x, size_t y, size_t z);
    void BreakBlock(size_t x, size_t y, size_t z);
    void UpdateMesh();
};

#endif //!VOX_CHUNK_H
