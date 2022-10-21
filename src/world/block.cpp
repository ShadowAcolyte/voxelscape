#include "block.h"

bool Block::IsTransparent() const
{
    return meta & 0x40;
}

void Block::SetTrasnparent(bool transparent)
{
    meta &= ~0x40;
    meta |= static_cast<uint16_t>(transparent) << 6;
}

bool Block::IsFaceVisible(Direction dir) const
{
    return meta & 1 << static_cast<int>(dir);
}

void Block::SetFaceVisible(Direction dir, bool visible)
{
    uint16_t pos = static_cast<uint16_t>(dir);
    meta &= ~(1 << pos);
    meta |= static_cast<uint16_t>(visible) << pos;
}
