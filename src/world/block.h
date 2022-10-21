#pragma once

#include <cstdint>

#include "block_id.h"
#include "direction.h"

struct Block
{
public:
    BlockID id;
    /**
     * meta format: (in order from least to most significant bit)
     * <16 bits> total
     * <first 6 bits> -> visibility of faces
     * <7th bit> -> transparent block or not
     */
    uint16_t meta;

    Block() : id(BlockID::AIR), meta(0)
    {
    }

    Block(BlockID id, uint16_t meta) : id(id), meta(meta)
    {
    }

    bool IsTransparent() const;
    void SetTrasnparent(bool transparent);

    bool IsFaceVisible(Direction dir) const;
    void SetFaceVisible(Direction dir, bool visible);
};
