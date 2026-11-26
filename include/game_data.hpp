#pragma once

#include "player.hpp"
#include "bullet.hpp"
#include "enemy.hpp"

struct GameData
{
    Player player{};

    std::vector<Bullet> bullets = {};
    std::vector<Enemy> enemies = {};
};
