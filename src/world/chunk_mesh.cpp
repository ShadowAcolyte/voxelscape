#include "chunk.h"

glm::vec3 NORMAL_LUT[] = {
    // NORTH
    {0, 0, -1},
    // SOUTH
    {0, 0, 1},
    // EAST
    {1, 0, 0},
    // WEST
    {-1, 0, 0},
    // TOP
    {0, 1, 0},
    // BOTTOM
    {0, -1, 0}};

glm::vec3 VERT_LUT[6][4] = {{// NORTH
                             {1, 0, 0},
                             {0, 0, 0},
                             {0, 1, 0},
                             {1, 1, 0}},
                            {// SOUTH
                             {0, 0, 1},
                             {1, 0, 1},
                             {1, 1, 1},
                             {0, 1, 1}},
                            {// EAST
                             {1, 0, 1},
                             {1, 0, 0},
                             {1, 1, 0},
                             {1, 1, 1}},
                            {// WEST
                             {0, 0, 0},
                             {0, 0, 1},
                             {0, 1, 1},
                             {0, 1, 0}},
                            {// TOP
                             {0, 1, 1},
                             {1, 1, 1},
                             {1, 1, 0},
                             {0, 1, 0}},
                            {// BOTTOM
                             {1, 0, 1},
                             {0, 0, 1},
                             {0, 0, 0},
                             {1, 0, 0}}};

void Chunk::GenMesh()
{
    mesh.indices.clear();
    mesh.vertices.clear();

    for (int x = 0; x < CHUNK_WIDTH; x++)
    {
        for (int y = 0; y < CHUNK_HEIGHT; y++)
        {
            for (int z = 0; z < CHUNK_DEPTH; z++)
            {
                Block *block = GetBlock(x, y, z);

                for (int i = 0; i < static_cast<int>(Direction::TOTAL); i++)
                {
                    if (block->IsFaceVisible(static_cast<Direction>(i)))
                    {
                        int idx = mesh.vertices.size();

                        mesh.vertices.push_back(
                            {position + glm::vec3(x, y, z) + VERT_LUT[i][0], NORMAL_LUT[i], {0, 0}, {0, 0, 0}});
                        mesh.vertices.push_back(
                            {position + glm::vec3(x, y, z) + VERT_LUT[i][1], NORMAL_LUT[i], {0, 0}, {0, 0, 0}});
                        mesh.vertices.push_back(
                            {position + glm::vec3(x, y, z) + VERT_LUT[i][2], NORMAL_LUT[i], {0, 0}, {0, 0, 0}});
                        mesh.vertices.push_back(
                            {position + glm::vec3(x, y, z) + VERT_LUT[i][3], NORMAL_LUT[i], {0, 0}, {0, 0, 0}});

                        mesh.indices.push_back(idx);
                        mesh.indices.push_back(idx + 1);
                        mesh.indices.push_back(idx + 2);
                        mesh.indices.push_back(idx + 2);
                        mesh.indices.push_back(idx + 3);
                        mesh.indices.push_back(idx);
                    }
                }
            }
        }
    }
}