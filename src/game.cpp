#include "game.hpp"

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "platform/input.hpp"

Game::Game()
{

}

Game::~Game()
{

}

bool Game::init(const glm::ivec2& size)
{
    player.m_position = glm::vec2(size) * 0.5f;

    return true;
}

bool Game::handleInput()
{
    p_move_direction = glm::vec2(0.0f);
    if (Input::isPressed(Key::W))
    {
        p_move_direction.y += 1.0f;
    }
    if (Input::isPressed(Key::A))
    {
        p_move_direction.x -= 1.0f;
    }
    if (Input::isPressed(Key::S))
    {
        p_move_direction.y -= 1.0f;
    }
    if (Input::isPressed(Key::D))
    {
        p_move_direction.x += 1.0f;
    }
    if (glm::length(p_move_direction) > 0.f)
        p_move_direction = glm::normalize(p_move_direction);

    p_rotate = 0.0f;
    if (Input::isPressed(Key::E))
    {
        p_rotate -= 1.0f;
    }
    if (Input::isPressed(Key::SPACE))
    {
        p_rotate += 1.0f;
    }

    return true;
}

bool Game::update(float dt)
{
    player.m_position += p_move_direction * dt * 100.f;
    player.m_rotation = glm::mod(player.m_rotation + p_rotate * dt * 90.f + 360.f, 360.f);

    return true;
}