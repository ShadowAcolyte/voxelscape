#include "block_atlas.h"
#include "block.h"
#include "../../graphics/texture.h"

static int TILE_SIZE;
static Texture ATLAS_TEXTURE;
static glm::vec2 BLOCK_TEXTURE_LOOKUP_TABLE[int(BlockID::TOTAL)][int(Direction::TOTAL)][4];

/* Convert grid coordinates to normalized texture coordinates
Grid index starts at top left corner (0, 0) and increase towards the right as
(0, 0), (0, 1), (0, 2)... and downwards as (0, 0), (1, 0), (2, 0)...*/
static void _WriteFaceTexcoords(glm::vec2* faceCoords, int i, int j)
{
    float base_x = static_cast<float>(TILE_SIZE) * j / ATLAS_TEXTURE.m_width;
    float base_y = static_cast<float>(TILE_SIZE) * i / ATLAS_TEXTURE.m_height;
    float offset_x = static_cast<float>(TILE_SIZE) / ATLAS_TEXTURE.m_width;
    float offset_y = static_cast<float>(TILE_SIZE) / ATLAS_TEXTURE.m_height;

    faceCoords[0] = glm::vec2(base_x,            base_y);
    faceCoords[1] = glm::vec2(base_x,            base_y + offset_y);
    faceCoords[2] = glm::vec2(base_x + offset_x, base_y + offset_y);
    faceCoords[3] = glm::vec2(base_x + offset_x, base_y);
}

/* @param tileSize - Size of each face in pixels */
void BlockAtlas::Init(const std::string& atlasFilePath, const std::string& textureType, int tileSize)
{
    TILE_SIZE = tileSize;
    ATLAS_TEXTURE = Texture(atlasFilePath, textureType);

    for (Direction d = Direction::NORTH; d < Direction::TOTAL; ++d)
    {
        BLOCK_TEXTURE_LOOKUP_TABLE[int(BlockID::AIR)][int(d)][0] = glm::vec2(0, 0);
        BLOCK_TEXTURE_LOOKUP_TABLE[int(BlockID::AIR)][int(d)][1] = glm::vec2(0, 0);
        BLOCK_TEXTURE_LOOKUP_TABLE[int(BlockID::AIR)][int(d)][2] = glm::vec2(0, 0);
        BLOCK_TEXTURE_LOOKUP_TABLE[int(BlockID::AIR)][int(d)][3] = glm::vec2(0, 0);
    }

    _WriteFaceTexcoords(BLOCK_TEXTURE_LOOKUP_TABLE[int(BlockID::GRASS)][int(Direction::TOP)], 0, 0);
    _WriteFaceTexcoords(BLOCK_TEXTURE_LOOKUP_TABLE[int(BlockID::GRASS)][int(Direction::BOTTOM)], 0, 2);
    for (Direction d = Direction::NORTH; d <= Direction::WEST; ++d)
        _WriteFaceTexcoords(BLOCK_TEXTURE_LOOKUP_TABLE[int(BlockID::GRASS)][int(d)], 0, 1);
}

/* Vertex number must be between 0 and 3.
Vertices are ordered from the TOP-LEFT
corner of a block going COUNTER-CLOCKWISE*/
glm::vec2 BlockAtlas::GetTextureCoords(Block* block, Direction direction, int vertexNum)
{
    return BLOCK_TEXTURE_LOOKUP_TABLE[int(block->m_id)][int(direction)][vertexNum];
}

void BlockAtlas::Bind()
{
    ATLAS_TEXTURE.Bind();
}
