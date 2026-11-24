#include "bullet.hpp"

#include <iostream>

Bullet::Bullet(
    glm::vec2 const& position,
    glm::vec2 const& direction,
    float lifetime = Bullet::base_lifetime
) : m_position(position), m_direction(direction), m_lifetime(lifetime) {}

void Bullet::update(float dt)
{
    if (m_timer >= m_lifetime) return;

    m_timer += dt;
    m_position += m_direction * dt * Bullet::speed;
}