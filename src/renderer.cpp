#include "renderer.hpp"
#include "window.hpp"
#include "game.hpp"
#include "camera.hpp"
#include "shader.hpp"

#include <cmath>
#include <iostream>
#include <algorithm>
#include <magic_enum.hpp>

void Renderer::render(const Game& game)
{
    const auto& gData = game.m_data; // game data

    renderBackground(game);
    
    if (!useShader()) return;
    updateProjectionMatrix();
    updateViewMatrixWithFallback();

    p_shader->setBool("useColor", false);

    {
        glm::vec3 playerColor = gData.player.m_color;
        if (game.m_paused) playerColor -= 0.2;
        p_shader->setVec3("color", playerColor);
    }

    renderRect(gData.player.m_position, glm::vec2(gData.player.m_size), gData.player.m_rotation);

    p_shader->setBool("useColor", true);
    p_shader->setVec3("color", glm::vec3(0.1f));
    for (const Bullet& bullet : gData.bullets)
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

    glm::vec2 halfDims = glm::vec2(window.getWinSize()) * 0.5f;
    
    m_projection = glm::ortho(
        -halfDims.x, halfDims.x,
        -halfDims.y, halfDims.y,
        -1.0f, 1.0f
    );

    initTextures();

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
            { { 0.5f,  0.5f}, {1.0f, 1.0f} },
            { {-0.5f,  0.5f}, {0.0f, 1.0f} },
            { {-0.5f, -0.5f}, {0.0f, 0.0f} },
            { { 0.5f, -0.5f}, {1.0f, 0.0f} }
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
    verts.emplace_back(glm::vec2{0.0f, 0.0f}, glm::vec2{0.5f, 0.5f}); // center
    
    for (std::size_t i = 0; i < Circle::segments; i++)
    {
        float angle = increment * static_cast<float>(i);

        float x = cosf(angle) * 0.5f;
        float y = sinf(angle) * 0.5f;
        float u = x + 0.5f;
        float v = y + 0.5f;

        verts.emplace_back(glm::vec2{x, y}, glm::vec2{u, v});

        inds.push_back(0);
        inds.push_back(i + 1);
        inds.push_back((i + 1) % Circle::segments + 1);
    }

    m_meshDatas[(int)Shape::Circle] = {
        .m_vertices = std::move(verts),
        .m_indices = std::move(inds)
    };
}

void Renderer::renderBackground(const Game& game) const
{
    GLfloat clearColor[4];
    glGetFloatv(GL_COLOR_CLEAR_VALUE, clearColor);
    if (game.m_paused)
    {
        constexpr float darkFactor = 0.1f;

        glClearColor(
            std::max(0.0f, clearColor[0] - darkFactor),
            std::max(0.0f, clearColor[1] - darkFactor),
            std::max(0.0f, clearColor[2] - darkFactor),
            clearColor[3]
        );
    }

    glClear(GL_COLOR_BUFFER_BIT);

    if (game.m_paused)
        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
}

bool Renderer::useShader() const
{
    if (!p_shader)
    {
        std::cout << "Renderer::render::ERROR: no shader given\n";
        return false;
    }

    p_shader->use();

    return true;
}

void Renderer::updateProjectionMatrix() const
{
    p_shader->setMat4("projection", m_projection);
}

void Renderer::updateViewMatrixWithFallback() const
{
    if (!p_camera)
    {
        std::cout << "Renderer::render::WARNING: no camera given. Using fallback (default)\n";
        Camera2D fallback_cam;

        p_shader->setMat4("view", fallback_cam.getViewMatrix());
    }
    else {
        p_shader->setMat4("view", p_camera->getViewMatrix());
    }
}

bool Renderer::initTextures()
{
    if (!loadTexture(Tex::Background, RESOURCES_PATH "assets/color_splash_bg.jpg")) return false;

    return true;
}

bool Renderer::loadTexture(Tex texture, std::string_view filepath)
{
    if (
        !m_textures[static_cast<int>(texture)]
        .loadFromFile(filepath)
    ){
        std::cout << std::format(
            "Failed to load '{}' texture. Path: {}\n",
            magic_enum::enum_name(texture), filepath
        );
        return false;
    }

    return true;
}

const Texture& Renderer::getTexture(Tex texture) const
{
    return m_textures[static_cast<int>(texture)];
}