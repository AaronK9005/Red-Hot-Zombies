#pragma once

#include "player.hpp"

void Player::move(glm::vec2 const& direction)
{
    m_position += direction * m_speed;
}