#pragma once

#include "pch.hpp"

struct Vertex
{
    glm::vec2 position{0.0f};
    glm::vec2 texCoords{0.0f};

    // Vertex(float x, float y, float u, float v) : position(x, y), texCoords(u, v) {}
    // Vertex(const glm::vec2& xy, float u, float v) : position(xy), texCoords(u, v) {}
    // Vertex(float x, float y, const glm::vec2& uv) : position(x, y), texCoords(uv) {}
    Vertex(const glm::vec2& xy, const glm::vec2& uv) : position(xy), texCoords(uv) {}

    static void setVertexAttribPtr()
    {
        // position
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);

        // texCoords
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
        glEnableVertexAttribArray(1);
    }
};
