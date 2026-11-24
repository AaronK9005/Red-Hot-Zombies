#include "player_input.hpp"

#include <glm/vec2.hpp>

bool PlayerInput::shouldMove() const
{
    return glm::length(moveDirection) > 0.0f;
}

void PlayerInput::sanitize()
{
    if (glm::length(moveDirection) > 0.0f) moveDirection = glm::normalize(moveDirection);
    else sprint = false;
}