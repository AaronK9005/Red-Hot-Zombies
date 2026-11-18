#pragma once

#include "pch.hpp"

struct VertexAttribPtr {
    GLint size = 0;
    GLenum type = GL_FLOAT;
    GLboolean normalized = GL_FALSE;
    GLsizei stride = 0;
    const void *ptr = nullptr;
};