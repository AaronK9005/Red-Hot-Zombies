#pragma once

#include "pch.hpp"

struct Vertex
{
    glm::vec2 position{0.f};

    Vertex(float x, float y) : position(x, y) {}
    Vertex(const glm::vec2 vec) : position(vec) {}

    static void setVertexAttribPtr()
    {
        // position
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
        glEnableVertexAttribArray(0);
    }
};
