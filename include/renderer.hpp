#pragma once

#include "pch.hpp"

#include "mesh.hpp"
#include "shape.hpp"
#include "texture.hpp"

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

    Camera2D *p_camera = nullptr;
    Shader *p_shader = nullptr;
    glm::mat4 m_projection = glm::mat4(1.0f);
    std::array<Mesh, MESH_COUNT> m_meshes;
    std::array<MeshData, MESH_COUNT> m_meshDatas;
    std::array<Texture, TEXTURE_COUNT> m_textures;

public:
    bool init(const Window& window);
    void render(const Game& game);
    void setCamera(Camera2D& camera) { p_camera = &camera; }
    void setShader(Shader& shader) { p_shader = &shader; }
    glm::mat4 getProjectionMatrix() const { return m_projection; }

private:
    bool loadTexture(Tex texture, std::string_view filepath);
    const Texture& getTexture(Tex texture) const;

    bool useShader() const;
    void updateProjectionMatrix() const;
    void updateViewMatrixWithFallback() const;

    void renderRect(const glm::vec2& position, const glm::vec2& size) const;
    void renderRect(const glm::vec2& position, const glm::vec2& size, float rotation) const;
    void renderCircle(const glm::vec2& center, float radius) const;

    void renderBackground(const Game& game) const;

    void initRectMeshData();
    void initCircleMeshData();
    bool initTextures();
};
