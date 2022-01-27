#ifndef GAIA_BLOCKID_H
#define GAIA_BLOCKID_H

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

#endif