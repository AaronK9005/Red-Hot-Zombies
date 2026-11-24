#pragma once

#include "pch.hpp"

#include "player_input.hpp"
#include "game_data.hpp"
#include "game_state.hpp"

struct Game
{
    GameState m_state = GameState::Playing;

    GameData m_data{};

    bool m_paused = false;

    Game();
    ~Game();

    bool init(const glm::ivec2& size);
    PlayerInput handleInput();
    void update(const PlayerInput& input, float dt);
private:
    void updateBullets(float dt); // returns new number of bullets
};