#pragma once

#include <glm/vec3.hpp>

enum class Direction : uint16_t
{
    NORTH = 0, // -z
    SOUTH,     // +z
    EAST,      // +x
    WEST,      // -x
    TOP,       // +y
    BOTTOM,    // -y
    TOTAL
};
