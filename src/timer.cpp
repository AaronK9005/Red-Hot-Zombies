#include "timer.hpp"

void Timer::start(std::chrono::milliseconds duration)
{
    m_expirationTime = Clock::now() + duration;
}

bool Timer::isExpired() const
{
    return Clock::now() >= m_expirationTime;
}

RepeatingTimer::RepeatingTimer(Clock::duration duration) : m_duration(duration) {}

bool RepeatingTimer::update()
{
    // if (m_duration <= Clock::duration::zero()) return false;

    auto now = Clock::now();

    if (now < m_nextTrigger) return false;

    do {
        m_nextTrigger += m_duration;
    } while (m_nextTrigger < now);

    return true;   
}

void RepeatingTimer::reset()
{
    m_nextTrigger = Clock::now() + m_duration;
}