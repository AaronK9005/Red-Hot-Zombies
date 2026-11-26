#include "components/health.hpp"

#include <algorithm>

HealthComponent::HealthComponent(int max) : m_maxHealth(max), m_health(max) {}

int HealthComponent::modify(int value)
{
    m_health = std::clamp(m_health + value, 0, m_maxHealth);
    return m_health;
}

float HealthComponent::percentage() const
{
    return 
        static_cast<float>(m_health) /
        static_cast<float>(m_maxHealth);
}
