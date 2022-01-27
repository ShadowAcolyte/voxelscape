#include "chunk.h"
#include "../direction.h"

Chunk::Chunk(int x, int y, int z)
{
    position = glm::ivec3(x, y, z);
    blocks.reserve(CHUNK_VOLUME);
    for (int i = 0; i < CHUNK_VOLUME; i++)
        blocks.push_back(block::create());
}

void Chunk::place_block(block::Block b, size_t x, size_t y, size_t z)
{
    this->get_block(x, y, z) = b;

    // the block towards the SOUTH has its NORTH face not visible anymore, and so on
    //if (z > 0)                  block::set_face(get_block(x, y, z - 1), direction::NORTH,  0);
    //if (z < CHUNK_SIZE - 1)     block::set_face(get_block(x, y, z + 1), direction::SOUTH,  0);
    //if (x > 0)                  block::set_face(get_block(x - 1, y, z), direction::EAST,   0);
    //if (x < CHUNK_SIZE - 1)     block::set_face(get_block(x + 1, y, z), direction::WEST,   0);
    //if (y > 0)                  block::set_face(get_block(x, y - 1, z), direction::TOP,    0);
    //if (y < CHUNK_SIZE - 1)     block::set_face(get_block(x, y + 1, z), direction::BOTTOM, 0);
}

void Chunk::destroy_block(size_t x, size_t y, size_t z)
{
    this->get_block(x, y, z) = block::create();

    // the block towards the SOUTH has its NORTH face visible, and so on
    //if (z > 0)                  block::set_face(get_block(x, y, z - 1), direction::NORTH,  1);
    //if (z < CHUNK_SIZE - 1)     block::set_face(get_block(x, y, z + 1), direction::SOUTH,  1);
    //if (x > 0)                  block::set_face(get_block(x - 1, y, z), direction::EAST,   1);
    //if (x < CHUNK_SIZE - 1)     block::set_face(get_block(x + 1, y, z), direction::WEST,   1);
    //if (y > 0)                  block::set_face(get_block(x, y - 1, z), direction::TOP,    1);
    //if (y < CHUNK_SIZE - 1)     block::set_face(get_block(x, y + 1, z), direction::BOTTOM, 1);
}

void Chunk::destroy_chunk()
{
    blocks.clear();
}
