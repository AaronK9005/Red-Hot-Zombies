#include "timer.hpp"

Timer::Timer() : lastTime(Clock::now()) {}

float Timer::getDeltaTime()
{
    auto currentTime = Clock::now();

    float dt = std::chrono::duration<float>(currentTime - lastTime).count();

    lastTime = currentTime;

    return dt;
}