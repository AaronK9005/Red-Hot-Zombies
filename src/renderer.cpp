#include "renderer.hpp"
#include "window.hpp"
#include "game.hpp"
#include "camera.hpp"
#include "shader.hpp"
#include "platform/debug.hpp"

#include <cmath>
#include <iostream>
#include <algorithm>
#include <magic_enum.hpp>

// debug
#include "timer.hpp"

void Renderer::render(const Game& game)
{
    const auto& gData = game.m_data; // game data

    // game.m_paused
    clearFrame();

    float brightness = game.m_paused ? PAUSE_BRIGHTNESS : 1.0f;
    
    m_shader->use();
    m_shader->setFloat("brightness", brightness);
    m_shader->setMat4("view", m_camera->getViewMatrix());

    renderBackground(game);
    glCheckError();

    m_shader->setBool("useColor", true);
    m_shader->setVec3("color", gData.player.m_color);
    renderRect(gData.player.m_position, glm::vec2(gData.player.m_size), gData.player.m_rotation);

    m_shader->setBool("useColor", true);
    m_shader->setVec3("color", glm::vec3(0.1f));
    for (const Bullet& bullet : gData.bullets)
    {
        renderCircle(bullet.m_position, Bullet::radius);
    }
}

bool Renderer::init(const Window& window, const Shader& shader, const Camera2D& camera)
{
    initRectMeshData();
    initCircleMeshData();

    for (std::size_t i = 0; i < MESH_COUNT; i++)
    {
        m_meshes[i].init(m_meshDatas[i]);
    }

    if (!initTextures())
    {
        std::cout << "Failed to init textures\n";
        return false;
    }

    if (!m_bgShader.compile(SHADERS_PATH "basic.vert", SHADERS_PATH "background.frag"))
    {
        std::cout << "Renderer::init(): Failed to compile background shader\n";
        return false;
    }
    
    setViewportSize(window.getWinSize());
    setShader(shader);
    setCamera(camera);

    setClearColor(CLEAR_COLOR);

    // glDisable(GL_BLEND);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    return true;
}

#pragma region |> render helpers <|

void Renderer::clearFrame() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::renderRect(const glm::vec2& position, const glm::vec2& size) const
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(size, 0.0f));

    m_shader->setMat4("model", model);

    m_meshes[(int)Shape::Rect].draw();
}

void Renderer::renderRect(const glm::vec2& position, const glm::vec2& size, float rotation_rad) const
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::rotate(model, rotation_rad, Axis::Z);
    model = glm::scale(model, glm::vec3(size, 1.0f));

    m_shader->setMat4("model", model);

    m_meshes[(int)Shape::Rect].draw();
}

void Renderer::renderCircle(const glm::vec2& center, float radius) const
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(center, 0.0f));
    model = glm::scale(model, glm::vec3(radius, radius, 0.0f));

    m_shader->setMat4("model", model);

    m_meshes[(int)Shape::Circle].draw();
}

void Renderer::renderBackground(const Game& game) const
{
    // glDisable(GL_DEPTH_TEST);
    // glDepthMask(GL_FALSE);

    m_bgShader.use();

    getTexture(Tex::Background).bind(TexUnit::u0);
    m_bgShader.setInt("bgTexture", 0);

    glm::vec2 offset = game.m_data.player.m_position / m_viewportSize;
    /*glm::mod(game.m_data.player.m_position, m_viewportSize)*/ 

    m_bgShader.setVec2("offset", offset);

    float opacity = game.m_paused ? PAUSE_OPACITY : 0.75f;
    m_bgShader.setFloat("opacity", opacity);

    glm::mat4 model{1.0f};

    model = glm::translate(model, glm::vec3(game.m_data.player.m_position, 0.0f));
    model = glm::scale(model, glm::vec3(m_viewportSize, 1.0f));
    
    m_bgShader.setMat4("model", model);
    m_bgShader.setMat4("view", m_camera->getViewMatrix());
    m_bgShader.setMat4("projection", m_projection);

    m_meshes[(int)Shape::Rect].draw();

    m_shader->use();

    // glDepthMask(GL_TRUE);
    // glEnable(GL_DEPTH_TEST);
}

#pragma endregion ---------------------------------

#pragma region |> init helpers <|

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

bool Renderer::initTextures()
{
    Texture::flipVerticallyOnLoad(true);

    if (!loadTexture(Tex::Background, RESOURCES_PATH "assets/color_splash_bg.jpg")) return false;
    getTexture(Tex::Background).setWrappings(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);

    return true;
}

#pragma endregion ---------------------------------

#pragma region |> resources managers <|

    #pragma region |> set <|

    void Renderer::setClearColor(glm::vec3 const& color) const
    {
        glClearColor(color.x, color.y, color.z, 1.0f);
    }
    
    void Renderer::setCamera(const Camera2D& camera)
    {
        m_camera = &camera;
    }
    
    void Renderer::setShader(const Shader& shader)
    {
        m_shader = &shader;
        
        shader.use();
        shader.setMat4("projection", m_projection);
    }

    void Renderer::setViewportSize(glm::vec2 const& viewport)
    {
        if (m_viewportSize != viewport)
        {
            m_viewportSize = viewport;
        }

        updateProjectionMatrix();
    }

    #pragma endregion ---------------------------------

    #pragma region |> get <|

    const Texture& Renderer::getTexture(Tex texture) const
    {
        return m_textures[static_cast<int>(texture)];
    }
    
    #pragma endregion ---------------------------------

    #pragma region |> other managers <|
    void Renderer::updateProjectionMatrix()
    {
        m_projection = glm::mat4(1.0f);

        glm::vec2 halfDims = glm::vec2(m_viewportSize * 0.5f);
        
        m_projection = glm::ortho(
            -halfDims.x, halfDims.x,
            -halfDims.y, halfDims.y,
            -1.0f, 1.0f
        );

        if (m_shader) m_shader->setMat4("projection", m_projection);
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

    #pragma endregion ---------------------------------

#pragma endregion ---------------------------------
