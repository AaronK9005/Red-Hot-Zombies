#pragma once

#include "player.hpp"

void Player::move(glm::vec2 const& direction)
{
    m_position += direction * m_speed;
}

glm::vec2 Player::lookAt(glm::vec2 const& point)
{
    glm::vec2 dir = glm::normalize(point - m_position);

    m_rotation = glm::degrees(glm::atan(dir.y, dir.x));

    return dir;
}