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
    p_position = glm::vec2(size) * 0.5f;

    float vecticies[] = {
         0.5f,  0.5f, // top right
        -0.5f,  0.5f, // top left
        -0.5f, -0.5f, // bottom left
         0.5f, -0.5f  // bottom right
    };

    unsigned indicies[] = {
        0, 1, 2,
        0, 2, 3
    };

    // unsigned vbo, vao, ebo;

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vecticies), vecticies, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    // positions
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    m_projection = glm::ortho(
        0.0f, static_cast<float>(size.x),
        0.0f, static_cast<float>(size.y),
        -1.0f, 100.0f
        // static_cast<float>(-size.x / 2), static_cast<float>(size.x / 2),
        // static_cast<float>(-size.y / 2), static_cast<float>(size.y / 2),
        // -1.0f, 1.0f
    );

    if (!m_shader.compile(SHADERS_PATH "basic.vert", SHADERS_PATH "basic.frag"))
    {
        return false;
    }

    m_shader.use();
    m_shader.setVec3("player_color", p_color);
    // m_shader.setMat4("model", m_model);
    m_shader.setMat4("view", glm::mat4(1.0f));
    // m_shader.setMat4("projection", m_projection);

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
        p_rotate += 1.0f;
    }
    if (Input::isPressed(Key::SPACE))
    {
        p_rotate -= 1.0f;
    }

    return true;
}

bool Game::update(float dt)
{
    p_position += p_move_direction * dt * 100.f;
    p_rotation = glm::mod(p_rotation + p_rotate * dt * 90.f + 360.f, 360.f);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(p_position, 0.0f));
    model = glm::rotate(model, glm::radians(p_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(p_size, 0.0f));
    m_model = model;

    return true;
}

bool Game::render(const glm::ivec2& size)
{
    m_projection = glm::ortho(
        0.0f, static_cast<float>(size.x),
        0.0f, static_cast<float>(size.y),
        -1.0f, 1.0f
    );

    m_shader.use();
    m_shader.setMat4("projection", m_projection);
    m_shader.setMat4("model", m_model);

    glBindVertexArray(vao);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    return true;
}

