#include "game.hpp"

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Game::Game()
{

}

Game::~Game()
{

}

bool Game::init(const glm::ivec2& size)
{
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
        // 0.0f, static_cast<float>(size.x),
        // static_cast<float>(size.y), 0.0f,
        // -1.0f, 100.0f
        static_cast<float>(-size.x / 2), static_cast<float>(size.x / 2),
        static_cast<float>(-size.y / 2), static_cast<float>(size.y / 2),
        -1.0f, 1.0f
    );

    m_model = glm::scale(m_model, glm::vec3(100.f, 100.f, 1.0f));

    if (!m_shader.compile(SHADERS_PATH "basic.vert", SHADERS_PATH "basic.frag"))
    {
        return false;
    }

    m_shader.use();
    m_shader.setVec3("player_color", p_color);
    m_shader.setMat4("model", m_model);
    m_shader.setMat4("view", glm::mat4(1.0f));
    m_shader.setMat4("projection", m_projection);

    return true;
}

bool Game::handleInput()
{
    return true;
}

bool Game::update(float dt)
{
    return true;
}

bool Game::render(const glm::ivec2& size)
{
    m_projection = glm::ortho(
        // 0.0f, static_cast<float>(size.x),
        // 0.0f,
        // static_cast<float>(size.y),  0.0f,
        // -1.0f, 100.0f
        static_cast<float>(-size.x / 2), static_cast<float>(size.x / 2),
        static_cast<float>(-size.y / 2), static_cast<float>(size.y / 2),
        -1.0f, 1.0f
    );

    m_shader.setMat4("projection", m_projection);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    return true;
}

