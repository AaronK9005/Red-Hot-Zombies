#pragma once

#include "components/health.hpp"
#include "components/position.hpp"

struct Player : public PositionComponent, public HealthComponent
{
    static constexpr float SPRINT_MOD = 2.f;

    float m_size = 50.0f;
    float m_speed = 100.0f;

    glm::vec3 m_color{0.2f, 0.2f, 0.6f};

    void move(glm::vec2 const& direction);

};