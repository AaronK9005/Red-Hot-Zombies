#pragma once

#include "pch.hpp"

#include "mesh.hpp"
#include "shape.hpp"
// #include "texture.hpp"

struct Game;
class Window;
class Camera2D;
class Shader;
class Texture;

class Renderer {
    static constexpr std::size_t MESH_COUNT = static_cast<std::size_t>(Shape::COUNT);

    Camera2D *p_camera = nullptr;
    Shader *p_shader = nullptr;
    glm::mat4 m_projection = glm::mat4(1.0f);
    std::array<Mesh, MESH_COUNT> m_meshes;
    std::array<MeshData, MESH_COUNT> m_meshDatas;

public:
    bool init(const Window& window);
    void render(const Game& game);
    void setCamera(Camera2D& camera) { p_camera = &camera; }
    void setShader(Shader& shader) { p_shader = &shader; }
    glm::mat4 getProjectionMatrix() const { return m_projection; }

private:
    void renderRect(const glm::vec2& position, const glm::vec2& size) const;
    void renderRect(const glm::vec2& position, const glm::vec2& size, float rotation) const;
    void renderCircle(const glm::vec2& center, float radius) const;

    void renderBackground(const Texture& texture) const;

    void initRectMeshData();
    void initCircleMeshData();
};
