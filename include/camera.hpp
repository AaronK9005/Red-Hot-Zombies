#pragma once

#include "pch.hpp"

class Camera2D
{
    glm::vec2 m_position{0.0f};
    float m_rotation = 0.0f;
    float m_zoom = 1.0f;

public:
    Camera2D() = default;
    Camera2D(float pos_x, float pos_y) : m_position(pos_x, pos_y) {}
    Camera2D(glm::vec2 const& position) : m_position(position) {}

    void setPosition(glm::vec2 const& position) { m_position = position; }
    void setRotation(float rotation) { m_rotation = rotation; }
    void defaultZoom() { m_zoom = 1.0f; }

    void zoom(float offset) { m_zoom += offset; }
    void rotate(float offset) { m_rotation += offset; }
    void translate(glm::vec2 const& offset) { m_position += offset; }

    glm::mat4 getViewMatrix() const;
};