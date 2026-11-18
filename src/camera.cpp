#include "camera.hpp"

glm::mat4 Camera2D::getViewMatrix() const
{
    glm::mat4 view(1.0f);

    view = glm::translate(view, glm::vec3(m_position, 0.0f));
    view = glm::rotate(view, glm::radians(m_rotation), Axis::Z);
    view = glm::scale(view, glm::vec3(m_zoom, m_zoom, 1.0f));

    return view;
}