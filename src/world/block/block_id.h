#ifndef VOX_BLOCKID_H
#define VOX_BLOCKID_H

#include <cstdint>

enum class BlockID : uint16_t
{
    AIR = 0,
    DIRT,
    GRASS,
    TOTAL
};

#endif // !VOX_BLOCKID_H
