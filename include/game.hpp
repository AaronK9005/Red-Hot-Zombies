#pragma once

enum class GameState
{
    Title, Playing, Pause, Win
};

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "shader.hpp"

struct Game
{
    GameState m_state = GameState::Playing;

    float p_rotate = 0.0f; // in handle input, 0 = none, 1 = right, -1 left
    float p_rotation = 0.0f;
    glm::vec2 p_position{0.0f};
    glm::vec2 p_move_direction{0.0f};
    glm::vec2 p_size{50.f};
    glm::vec3 p_color{0.7f, 0.3f, 0.7};

    glm::mat4 m_projection{1.0f};
    glm::mat4 m_model{1.0f};
    unsigned vao = 0, vbo = 0, ebo = 0;
    Shader m_shader{};

    Game();
    ~Game();

    bool init(const glm::ivec2& size);
    bool handleInput();
    bool update(float dt);
    bool render(const glm::ivec2& size);
};