#include "chunk.h"
#include "../block/block_atlas.h"

static const glm::vec3 VERTEX_LOOKUP_TABLE[int(Direction::TOTAL)][4] = {
    {glm::vec3(1, 1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)},
    {glm::vec3(0, 1, 1), glm::vec3(0, 0, 1), glm::vec3(1, 0, 1), glm::vec3(1, 1, 1)},
    {glm::vec3(1, 1, 1), glm::vec3(1, 0, 1), glm::vec3(1, 0, 0), glm::vec3(1, 1, 0)},
    {glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 1)},
    {glm::vec3(0, 1, 0), glm::vec3(0, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 0)},
    {glm::vec3(1, 0, 0), glm::vec3(1, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 0)},
};

static const glm::vec3 NORMAL_LOOKUP_TABLE[int(Direction::TOTAL)] = {
    glm::vec3( 0,  0, -1),
    glm::vec3( 0,  0,  1),
    glm::vec3( 1,  0,  0),
    glm::vec3(-1,  0,  0),
    glm::vec3( 0,  1,  0),
    glm::vec3( 0, -1,  0)
};

void Chunk::PlaceBlock(const Block& block, size_t x, size_t y, size_t z)
{
    if (block.m_id == BlockID::AIR)
    {
        BreakBlock(x, y, z);
        return;
    }

    m_blocks[x + y * CHUNK_AREA + z * CHUNK_SIZE] = block;
    /* Update faces */
    if (x < CHUNK_SIZE - 1) {
        if (GetBlockPtr(x + 1, y, z)->m_id != BlockID::AIR)     // EAST BLOCK
        {
            GetBlockPtr(x + 1, y, z)->SetVisible(Direction::WEST, false);
            GetBlockPtr(x, y, z)->SetVisible(Direction::EAST, false);
        }
    }
    if (x > 0) {
        if (GetBlockPtr(x - 1, y, z)->m_id != BlockID::AIR)     // WEST BLOCK
        {
            GetBlockPtr(x - 1, y, z)->SetVisible(Direction::EAST, false);
            GetBlockPtr(x, y, z)->SetVisible(Direction::WEST, false);
        }
    }
    if (z > 0) {
        if (GetBlockPtr(x, y, z - 1)->m_id != BlockID::AIR)     // NORTH BLOCK
        {
            GetBlockPtr(x, y, z - 1)->SetVisible(Direction::SOUTH, false);
            GetBlockPtr(x, y, z)->SetVisible(Direction::NORTH, false);
        }
    }
    if (z < CHUNK_SIZE - 1) {
        if (GetBlockPtr(x, y, z + 1)->m_id != BlockID::AIR)     // SOUTH BLOCK
        {
            GetBlockPtr(x, y, z + 1)->SetVisible(Direction::NORTH, false);
            GetBlockPtr(x, y, z)->SetVisible(Direction::SOUTH, false);
        }
    }
    if (y < CHUNK_SIZE - 1) {
        if (GetBlockPtr(x, y + 1, z)->m_id != BlockID::AIR)     // TOP BLOCK
        {
            GetBlockPtr(x, y + 1, z)->SetVisible(Direction::BOTTOM, false);
            GetBlockPtr(x, y, z)->SetVisible(Direction::TOP, false);
        }
    }
    if (y > 0) {
        if (GetBlockPtr(x, y - 1, z)->m_id != BlockID::AIR)     // BOTTOM BLOCK
        {
            GetBlockPtr(x, y - 1, z)->SetVisible(Direction::TOP, false);
            GetBlockPtr(x, y, z)->SetVisible(Direction::BOTTOM, false);
        }
    }
}

void Chunk::BreakBlock(size_t x, size_t y, size_t z)
{
    m_blocks[x + y * CHUNK_AREA + z * CHUNK_SIZE] = Block(BlockID::AIR);
    /* Update faces */
    GetBlockPtr(x + 1, y, z)->SetVisible(Direction::WEST, true);    // EAST BLOCK
    GetBlockPtr(x - 1, y, z)->SetVisible(Direction::EAST, true);    // WEST BLOCK
    GetBlockPtr(x, y, z - 1)->SetVisible(Direction::SOUTH, true);   // NORTH BLOCK
    GetBlockPtr(x, y, z + 1)->SetVisible(Direction::NORTH, true);   // SOUTH BLOCK
    GetBlockPtr(x, y + 1, z)->SetVisible(Direction::BOTTOM, true);  // TOP BLOCK
    GetBlockPtr(x, y - 1, z)->SetVisible(Direction::TOP, true);     // BOTTOM BLOCK
}

void Chunk::UpdateMesh()
{
    m_mesh.m_vertices.clear();
    m_mesh.m_indices.clear();

    // create new mesh
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                Block* block = GetBlockPtr(x, y, z);
                if (block->m_id != BlockID::AIR)
                {
                    int offset = m_mesh.m_vertices.size();
                    for (Direction d = Direction::NORTH; d < Direction::TOTAL; ++d)
                    {
                        if (block->GetVisible(d))
                        {
                            for (int vertex = 0; vertex < 4; vertex++)
                                m_mesh.m_vertices.push_back(Vertex(VERTEX_LOOKUP_TABLE[int(d)][vertex]
                                                                    + glm::vec3(x, y, z) + glm::vec3(m_position), // position
                                    NORMAL_LOOKUP_TABLE[int(d)],    // normal vector
                                    BlockAtlas::GetTextureCoords(block, d, vertex), // uv coords
                                    glm::vec3(1, 1, 1)));   // color
                            m_mesh.m_indices.push_back(offset + 0);
                            m_mesh.m_indices.push_back(offset + 1);
                            m_mesh.m_indices.push_back(offset + 2);
                            m_mesh.m_indices.push_back(offset + 2);
                            m_mesh.m_indices.push_back(offset + 3);
                            m_mesh.m_indices.push_back(offset + 0);
                            offset += 4;
                        }
                    }
                }
            }
        }
    }
}
