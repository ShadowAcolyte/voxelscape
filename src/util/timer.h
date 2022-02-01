#ifndef VOX_TIME_H
#define VOX_TIME_H

#include <cstdint>

namespace Timer
{
    void Tick();

    inline int64_t GetCurrTimeNs() {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    }
    int64_t GetDeltaNs();
    float GetDeltaUs();
    float GetDeltaMs();
    float GetDeltaMsAvg();
    int GetFps();
    int GetFpsAvg();
}

#endif // !VOX_TIME_H
