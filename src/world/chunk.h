#pragma once

#include "../graphics/mesh.h"
#include "block.h"
#include <glm/vec3.hpp>
#include <vector>

// x axis
#define CHUNK_WIDTH 32
// y axis
#define CHUNK_HEIGHT 32
//  z axis
#define CHUNK_DEPTH 32

class Chunk
{
public:
    glm::vec3 position;
    std::vector<Block> blocks;
    Mesh mesh;

    Chunk() : position(0, 0, 0), blocks(CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH)
    {
    }
    Chunk(float x, float y, float z) : position(x, y, z), blocks(CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH)
    {
    }

    void PlaceBlock(int x, int y, int z, const Block &block);
    Block *GetBlock(int x, int y, int z);
    Block *GetBlock(const glm::ivec3 &pos);

    void GenMesh();
};
