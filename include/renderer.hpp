#pragma once

#include "pch.hpp"

#include "mesh.hpp"
#include "shape.hpp"
#include "texture.hpp"
#include "shader.hpp"

struct Game;
class Window;
class Camera2D;
class Shader;
// class Texture;

enum class Tex
{
    Background, Player, Bullet, COUNT
};

class Renderer {
    static constexpr std::size_t MESH_COUNT = static_cast<std::size_t>(Shape::COUNT);
    static constexpr std::size_t TEXTURE_COUNT = static_cast<std::size_t>(Tex::COUNT);

    static constexpr glm::vec3 CLEAR_COLOR{0.4f, 0.4f, 0.2f};

    glm::vec2 m_viewportSize = { 800, 600 };
    const Camera2D *m_camera = nullptr;
    const Shader *m_shader = nullptr;
    glm::mat4 m_projection = glm::mat4(1.0f);
    std::array<Mesh, MESH_COUNT> m_meshes;
    std::array<MeshData, MESH_COUNT> m_meshDatas;
    std::array<Texture, TEXTURE_COUNT> m_textures;

    Shader m_bgShader{};

public:
    bool init(const Window& window, const Shader& shader, const Camera2D& camera);
    void render(const Game& game);
    void setCamera(const Camera2D& camera);
    void setShader(const Shader& shader);
    void setViewportSize(glm::vec2 const& viewport);
    glm::mat4 getProjectionMatrix() const { return m_projection; }

private:
    bool loadTexture(Tex texture, std::string_view filepath);
    const Texture& getTexture(Tex texture) const;

    void updateProjectionMatrix();
    void setViewMatrixWithFallback() const;

    void setClearColor(glm::vec3 const& color) const;
    void clearFrame() const;

    void renderRect(const glm::vec2& position, const glm::vec2& size) const;
    void renderRect(const glm::vec2& position, const glm::vec2& size, float rotation) const;
    void renderCircle(const glm::vec2& center, float radius) const;

    void renderBackground(const Game& game) const;

    bool initBackgroundShader();
    void initRectMeshData();
    void initCircleMeshData();
    bool initTextures();
};
