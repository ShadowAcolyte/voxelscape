#ifndef GAIA_BLOCK_H
#define GAIA_BLOCK_H

#include <cstdint>

#include "blockid.h"
#include "../direction.h"

namespace block
{
    /* Starting from the left:
       bits 0-5: face data
       bits 6-15: block id */
    typedef uint32_t Block;

    /* All 6 sides are visible by default 0x3F = 0b111111*/
    constexpr Block create() noexcept
    {
        return uint32_t(0x0000003F);
    }

    inline Block create(blockid::ID id) noexcept
    {
        return uint32_t(0x0000003F) | (id << 6);
    }

    inline blockid::ID get_id(const Block& b)
    {
        return blockid::ID((b >> 6) & 0x3FF);
    }

    /* Set visibility of a face */
    inline void set_face(Block& b, direction::DIR d, bool visible)
    {
        if (visible)
            b |= (1UL << d);
        else
            b &= ~(1UL << d);
    }

    /* Check if a face is visible */
    inline bool get_face(const Block& b, direction::DIR d)
    {
        return (b >> d) & 1UL;
    }
}

#endif // GAIA_BLOCK_H
