#pragma once

#include <glm/fwd.hpp>

struct Bullet
{
    static constexpr float speed = 1'000.0f;
    static constexpr float base_lifetime = 1.5f;
    static constexpr float radius = 10.f;

    glm::vec2 m_position{0.0f};
    glm::vec2 m_direction{0.0f};
    float m_lifetime = 1.0f;
    float m_timer = 0.0f;

    Bullet() = default;
    Bullet(glm::vec2 const& position, glm::vec2 const& direction, float lifetime);

    void update(float dt);
    bool isAlive() const { return m_lifetime > m_timer; }
};