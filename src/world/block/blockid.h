#ifndef VOX_BLOCKID_H
#define VOX_BLOCKID_H

#include <cstdint>

namespace blockid
{
    enum ID : uint32_t
    {
        AIR = 0,
        DIRT,
        GRASS
    };
}

#endif // !VOX_BLOCKID_H
