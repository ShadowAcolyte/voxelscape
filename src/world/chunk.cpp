#include "chunk.h"

void Chunk::PlaceBlock(int x, int y, int z, const Block &block)
{
    Block *chunkBlock = GetBlock(x, y, z);
    chunkBlock->id = block.id;
    chunkBlock->meta = block.meta;

    // update faces of surrounding blocks
    Block *other;
    bool transparency = block.IsTransparent();
    if (z > 0)
    {
        other = GetBlock(x, y, z - 1);
        // north block touches south of current block
        chunkBlock->SetFaceVisible(Direction::SOUTH, other->IsTransparent());
        other->SetFaceVisible(Direction::NORTH, transparency);
    }
    if (z < CHUNK_DEPTH)
    {
        other = GetBlock(x, y, z + 1);
        // south block touches north of current block
        chunkBlock->SetFaceVisible(Direction::NORTH, other->IsTransparent());
        other->SetFaceVisible(Direction::SOUTH, transparency);
    }
    if (x > 0)
    {
        other = GetBlock(x - 1, y, z);
        // west block touches east of current block
        chunkBlock->SetFaceVisible(Direction::EAST, other->IsTransparent());
        other->SetFaceVisible(Direction::WEST, transparency);
    }
    if (x < CHUNK_WIDTH)
    {
        other = GetBlock(x + 1, y, z);
        // east block touches west of current block
        chunkBlock->SetFaceVisible(Direction::WEST, other->IsTransparent());
        other->SetFaceVisible(Direction::EAST, transparency);
    }
    if (y > 0)
    {
        other = GetBlock(x, y - 1, z);
        // bottom block touches top of current block
        chunkBlock->SetFaceVisible(Direction::TOP, other->IsTransparent());
        other->SetFaceVisible(Direction::BOTTOM, transparency);
    }
    if (y < CHUNK_HEIGHT)
    {
        other = GetBlock(x, y + 1, z);
        // top block touches bottom of current block
        chunkBlock->SetFaceVisible(Direction::BOTTOM, other->IsTransparent());
        other->SetFaceVisible(Direction::TOP, transparency);
    }
}

Block *Chunk::GetBlock(int x, int y, int z)
{
    return &blocks.at(y * CHUNK_WIDTH * CHUNK_HEIGHT + z * CHUNK_WIDTH + x);
}

Block *Chunk::GetBlock(const glm::ivec3 &pos)
{
    return &blocks.at(pos.y * CHUNK_WIDTH * CHUNK_HEIGHT + pos.z * CHUNK_WIDTH + pos.x);
}
