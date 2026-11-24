#pragma once

#include "pch.hpp"

#include "player_input.hpp"
#include "player.hpp"
#include "bullet.hpp"

enum class GameState
{
    Title, Playing, Pause, Win
};

struct Game
{
    GameState m_state = GameState::Playing;

    Player player{};

    std::vector<Bullet> bullets;

    float p_rotate = 0.0f; // in handle input, 0 = none, 1 = right, -1 left
    glm::vec2 p_move_direction{0.0f};
    glm::vec3 p_color{0.7f, 0.3f, 0.7};

    Game();
    ~Game();

    bool init(const glm::ivec2& size);
    PlayerInput handleInput();
    void update(const PlayerInput& input, float dt);
private:
    void updateBullets(float dt); // returns new number of bullets
};