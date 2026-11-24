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
    player.m_position = glm::vec2(size) * 0.5f;

    return true;
}

PlayerInput Game::handleInput()
{
    PlayerInput input = {};

    input.moveDirection.x = Input::isPressed(Key::D) - Input::isPressed(Key::A);
    input.moveDirection.y = Input::isPressed(Key::W) - Input::isPressed(Key::S);
    
    if (Input::justPressed(Mouse::LEFT)) input.fire = true;

    input.sanitize();

    return input;
}

void Game::update(const PlayerInput& input, float dt)
{
    player.move(input.moveDirection * dt);

    glm::vec2 faceDir = player.lookAt(Input::getMousePos_world());

    if (input.fire)
    {
        bullets.emplace_back(player.m_position + faceDir * player.m_size / (float)glm::sqrt(2), faceDir, 1.0f);
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
    for (Bullet& bullet : bullets)
        bullet.update(dt);

    std::erase_if(bullets, [](const Bullet& bullet){
        return !bullet.isAlive();
    }); 
}