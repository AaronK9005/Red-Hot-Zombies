#include "game.hpp"

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "platform/input.hpp"
#include "timer.hpp"

Game::Game()
{

}

Game::~Game()
{

}

bool Game::init(const glm::ivec2& size)
{
    m_data.player.m_position = glm::vec2(size) * 0.5f;

    return true;
}

PlayerInput Game::handleInput()
{
    PlayerInput input = {};

    input.moveDirection.x = Input::isPressed(Key::D) - Input::isPressed(Key::A);
    input.moveDirection.y = Input::isPressed(Key::W) - Input::isPressed(Key::S);
    
    if (Input::justPressed(Mouse::LEFT)) input.fire = true;

    if (Input::isPressed(Key::SPACE)) input.sprint = true;

    if (Input::justPressed(Key::P)) input.togglePause = true;

    input.sanitize();

    return input;
}

void Game::update(const PlayerInput& input, float dt)
{
    if (input.togglePause) m_paused = !m_paused;
    if (m_paused)
    {
        return;
    }

    {
        glm::vec2 moveVec = input.moveDirection * dt;
        if (input.sprint) moveVec *= 2;

        m_data.player.move(moveVec);
    }

    glm::vec2 faceDir = m_data.player.lookAt(Input::getMousePos_world());

    if (input.fire)
    {
        m_data.bullets.emplace_back(
            m_data.player.m_position + faceDir * m_data.player.m_size / (float)glm::sqrt(2),
            faceDir,
            1.0f // lifetime in seconds
        );
    }

    updateBullets(dt);

    // static RepeatingTimer repTimer(milliseconds(500));

    // if (repTimer.update())
    // {
    //     std::cout << std::format("bullets: {}\n", bullets.size());
    // }
}

void Game::updateBullets(float dt)
{
    for (Bullet& bullet : m_data.bullets)
        bullet.update(dt);

    std::erase_if(m_data.bullets, [](const Bullet& bullet){
        return !bullet.isAlive();
    }); 
}