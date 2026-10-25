#pragma once

#include <chrono>

using Clock = std::chrono::high_resolution_clock;

struct Timer
{
    std::chrono::high_resolution_clock::time_point lastTime{};

    Timer();
    float getDeltaTime();
};