#ifndef VOX_TIME_H
#define VOX_TIME_H

#include <cstdint>

namespace timer
{
    void tick();

    int64_t get_delta_ns();
    float get_delta_us();
    float get_delta_ms();
    float get_delta_ms_avg();
    int get_fps();
    int get_fps_avg();
}

#endif // !VOX_TIME_H
