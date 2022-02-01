#ifndef VOX_DIRECTION_H
#define VOX_DIRECTION_H

enum class Direction : int
{
    NORTH  = 0,
    SOUTH  = 1,
    EAST   = 2,
    WEST   = 3,
    TOP    = 4,
    BOTTOM = 5,
    TOTAL  = 6
};

constexpr Direction& operator++(Direction& d) noexcept
{
    if (d == Direction::TOTAL)
        d = static_cast<Direction>(0);
    else
        d = static_cast<Direction>(static_cast<int>(d) + 1);
    return d;
}

#endif // !VOX_DIRECTION_H
