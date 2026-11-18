#pragma once

#include "pch.hpp"

#include "player.hpp"

enum class GameState
{
    Title, Playing, Pause, Win
};

struct Game
{
    GameState m_state = GameState::Playing;

    Player player{};

    float p_rotate = 0.0f; // in handle input, 0 = none, 1 = right, -1 left
    glm::vec2 p_move_direction{0.0f};
    glm::vec3 p_color{0.7f, 0.3f, 0.7};

    Game();
    ~Game();

    bool init(const glm::ivec2& size);
    bool handleInput();
    bool update(float dt);
};