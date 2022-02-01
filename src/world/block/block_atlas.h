#ifndef VOX_BLOCK_ATLAS_H
#define VOX_BLOCK_ATLAS_H

#include <glm/vec2.hpp>
#include <string>

class Block;
enum class Direction;

namespace BlockAtlas
{
    void Init(const std::string& atlasFilePath, const std::string& textureType, int tileSize);
    glm::vec2 GetTextureCoords(Block* block, Direction direction, int vertexNum);
    void Bind();
};

#endif // !VOX_BLOCK_ATLAS_H
