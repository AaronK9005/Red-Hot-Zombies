#include "renderer.hpp"
#include "window.hpp"
#include "game.hpp"
#include "camera.hpp"
#include "shader.hpp"

#include <cmath>
#include <iostream>

void Renderer::render(const Game& game)
{
    if (!p_shader)
    {
        std::cout << "Renderer::render::ERROR: no shader given\n";
        return;
    }
    p_shader->use();

    p_shader->setMat4("projection", m_projection);

    if (!p_camera)
    {
        std::cout << "Renderer::render::WARNING: no camera given\n";
        Camera2D fallback_cam;

        p_shader->setMat4("view", fallback_cam.getViewMatrix());
    }
    else {
        p_shader->setMat4("view", p_camera->getViewMatrix());
    }

    p_shader->setVec3("color", game.p_color);
    renderRect(game.player.m_position, glm::vec2(game.player.m_size), game.player.m_rotation);

    p_shader->setVec3("color", glm::vec3(0.1f));
    for (const Bullet& bullet : game.bullets)
    {
        renderCircle(bullet.m_position, Bullet::radius);
    }
}

bool Renderer::init(const Window& window)
{
    initRectMeshData();
    initCircleMeshData();

    for (std::size_t i = 0; i < MESH_COUNT; i++)
    {
        m_meshes[i].init(m_meshDatas[i]);
    }

    m_projection = glm::ortho(
        0.0f, static_cast<float>(window.getWinSize().x),
        0.0f, static_cast<float>(window.getWinSize().y),
        -1.0f, 1.0f
    );

    return true;
}

void Renderer::renderRect(const glm::vec2& position, const glm::vec2& size) const
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(size, 0.0f));

    p_shader->setMat4("model", model);

    m_meshes[(int)Shape::Rect].draw();
}

void Renderer::renderRect(const glm::vec2& position, const glm::vec2& size, float rotation) const
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), Axis::Z);
    model = glm::scale(model, glm::vec3(size, 0.0f));

    p_shader->setMat4("model", model);

    m_meshes[(int)Shape::Rect].draw();
}

void Renderer::renderCircle(const glm::vec2& center, float radius) const
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(center, 0.0f));
    model = glm::scale(model, glm::vec3(radius, radius, 0.0f));

    p_shader->setMat4("model", model);

    m_meshes[(int)Shape::Circle].draw();
}

void Renderer::initRectMeshData()
{
    m_meshDatas[(int)Shape::Rect] = MeshData{
        .m_vertices = {
            {  0.5f,  0.5f },
            { -0.5f,  0.5f },
            { -0.5f, -0.5f },
            {  0.5f, -0.5f }
        },
        .m_indices = {
            0, 1, 2,
            0, 2, 3
        }
    };
}

void Renderer::initCircleMeshData()
{
    std::vector<Vertex> verts;
    std::vector<unsigned> inds;
    verts.reserve(Circle::segments * 2 + 1);
    inds.reserve(Circle::segments * 3);

    const float increment = glm::radians(360.0f / Circle::segments);
    verts.emplace_back(0.0f, 0.0f); // center
    
    for (std::size_t i = 0; i < Circle::segments; i++)
    {
        float angle = increment * static_cast<float>(i);

        verts.emplace_back(cosf(angle), sinf(angle));

        inds.push_back(0);
        inds.push_back(i + 1);
        inds.push_back((i + 1) % Circle::segments + 1);
    }

    m_meshDatas[(int)Shape::Circle] = {
        .m_vertices = std::move(verts),
        .m_indices = std::move(inds)
    };
}