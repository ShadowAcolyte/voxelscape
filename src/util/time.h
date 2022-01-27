#ifndef GAIA_TIME_H

#include <cstdint>

namespace timer
{
    void tick();

    int64_t get_delta_ns();
    float get_delta_us();
    float get_delta_ms();
    float get_fps();
}

#endif // GAIA_TIME_H
