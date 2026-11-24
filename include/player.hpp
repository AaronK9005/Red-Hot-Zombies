#pragma once

#include "pch.hpp"

#include "bullet.hpp"

struct Player
{
    glm::vec2 m_position = glm::vec2(0.0f);
    float m_rotation = 0.0f;
    float m_size = 50.0f;
    float m_speed = 100.0f;

    glm::vec3 m_color{0.7f, 0.3f, 0.3f};

    void move(glm::vec2 const& direction);

    // sets rotation to face towards the given point (int world pos) and returns nomalized direction vector
    glm::vec2 lookAt(glm::vec2 const& point);
};