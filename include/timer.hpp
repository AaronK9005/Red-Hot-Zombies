#pragma once

#include <chrono>

using Clock = std::chrono::steady_clock;
using std::chrono::seconds;
using std::chrono::milliseconds;

struct Timer
{
    Clock::time_point m_expirationTime;

    void start(std::chrono::milliseconds duration);
    bool isExpired() const;
};

struct RepeatingTimer
{
    Clock::duration m_duration = seconds(1);
    Clock::time_point m_nextTrigger;

    RepeatingTimer(Clock::duration duration);

    bool update();
    void reset();
};
