#ifndef VOX_BLOCK_H
#define VOX_BLOCK_H

#include "../direction.h"
#include "block_id.h"

class Block
{
    /* Visible faces, all 6 sides visible by default */
    bool m_faces[static_cast<int>(Direction::TOTAL)] = { 1, 1, 1, 1, 1, 1 };
public:
    BlockID m_id;

    Block()
        : m_id(BlockID::AIR) {}

    Block(BlockID id)
        : m_id(id) {}

    inline void SetVisible(Direction direction, bool visible)
    {
        m_faces[static_cast<int>(direction)] = visible;
    }
    
    inline bool GetVisible(Direction direction)
    {
        return m_faces[static_cast<int>(direction)];
    }
};

#endif //!VOX_BLOCK_H
