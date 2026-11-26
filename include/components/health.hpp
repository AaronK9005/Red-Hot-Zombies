#pragma once

struct HealthComponent
{
    static constexpr int DEFAULT = 100;

    int m_health = DEFAULT;
    int m_maxHealth = DEFAULT;

    HealthComponent() = default;
    HealthComponent(int max);

    int modify(int value); // returns post modify health
    void die() { m_health = 0; }
    void max() { m_health = m_maxHealth; }
    float percentage() const;
};