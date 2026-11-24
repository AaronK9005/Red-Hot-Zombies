#include "player_input.hpp"

#include <glm/vec2.hpp>

bool PlayerInput::shouldMove() const
{
    return glm::length(moveDirection) > 0.0f;
}

void PlayerInput::sanitize()
{
    if (moveDirection.x != 0 || moveDirection.y != 0)
        moveDirection = glm::normalize(moveDirection);
    else sprint = false;
}