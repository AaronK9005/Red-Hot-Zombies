#include "components/position.hpp"

#include <cmath>

PositionComponent::PositionComponent(glm::vec2 const& position, float rotation_deg)
: m_position(position), m_rotation(glm::radians(rotation_deg)) {}

glm::vec2 PositionComponent::faceDir() const
{
    return {
        cosf(m_rotation),
        sinf(m_rotation)
    };
}

void PositionComponent::lookAt(glm::vec2 const& point)
{
    glm::vec2 dir = point - m_position;

    m_rotation = glm::atan(dir.y, dir.x);
}