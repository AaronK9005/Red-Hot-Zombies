#pragma once

#include <glm/fwd.hpp>

struct PositionComponent
{
    glm::vec2 m_position{0.0f};
    float m_rotation = 0.0f; // radians

    PositionComponent() = default;
    PositionComponent(glm::vec2 const& position, float rotation_deg = 0.0f);

    void setRotation(float deg) { m_rotation = glm::radians(deg); }
    float getRotation() const { return glm::degrees(m_rotation); }

    glm::vec2 faceDir() const;
    
    // sets rotation to face towards the given point (int world pos)
    void lookAt(glm::vec2 const& point);
};