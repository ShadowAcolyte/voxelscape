#include <chrono>

#include "timer.h"

static int64_t _previous_frame = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
static int64_t _current_frame = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
static int64_t _delta_ns;
static int64_t _avg_fps, _fps_clock, _fps_counter;

void timer::tick()
{
    _current_frame = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    _delta_ns = _current_frame - _previous_frame;
    _previous_frame = _current_frame;
    _fps_clock += _delta_ns;
    if (_fps_clock > 1000000000) {
        _avg_fps = _fps_counter;
        _fps_clock = _fps_counter = 0;
    }
    _fps_counter++;
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

float timer::get_delta_ms_avg()
{
    return 1000.0f / _avg_fps;
}

int timer::get_fps()
{
    return 1000000000 / _delta_ns;
}

int timer::get_fps_avg()
{
    return _avg_fps;
}
