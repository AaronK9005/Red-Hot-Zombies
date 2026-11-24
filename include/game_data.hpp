#pragma once

#include "player.hpp"
#include "bullet.hpp"

struct GameData
{
    Player player{};

    std::vector<Bullet> bullets = {};
};
