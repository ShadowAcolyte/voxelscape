#pragma once

#include <cstdint>

enum class BlockID : uint16_t
{
    NONE = 0,
    AIR,
    GRASS,
    STONE
};