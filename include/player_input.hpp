#pragma once

#include <glm/fwd.hpp>

struct PlayerInput
{
    glm::vec2 moveDirection{0.0f};
    bool fire = false;
    bool sprint = false;
    bool togglePause = false;

public:
    bool shouldMove() const;
    void sanitize();
};