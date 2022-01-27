#include <chrono>

#include "timer.h"

static int64_t _previous_frame = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
static int64_t _current_frame = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
static int64_t _delta_ns;

void timer::tick()
{
    _current_frame = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    _delta_ns = _current_frame - _previous_frame;
    _previous_frame = _current_frame;
}

int64_t timer::get_delta_ns()
{
    return _delta_ns;
}

float timer::get_delta_us()
{
    return _delta_ns / 1000.0f;
}

float timer::get_delta_ms()
{
    return _delta_ns / 1000000.0f;
}

float timer::get_fps()
{
    return 1000000000.0f / _delta_ns;
}
