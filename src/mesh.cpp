#include "mesh.hpp"

#include "platform/debug.hpp"

// Mesh::Mesh(std::span<const Vertex> vertices, std::span<const unsigned> indices)
// {
//     glGenBuffers(1, &m_vbo);
//     glGenBuffers(1, &m_ebo);
//     glGenVertexArrays(1, &m_vao);

//     glBindVertexArray(m_vao);
//     glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
//     // glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);
//     glBufferData(GL_ARRAY_BUFFER, vertices.size_bytes(), vertices.data(), GL_STATIC_DRAW);

//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
//     // glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), indices.data(), GL_STATIC_DRAW);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size_bytes(), indices.data(), GL_STATIC_DRAW);

//     // positions
//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);
// }

Mesh::Mesh(const MeshData& meshData)
{
    init(meshData);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}

void Mesh::init(const MeshData& meshData)
{
    std::span<const Vertex> vertices = meshData.m_vertices;
    std::span<const unsigned> indices = meshData.m_indices;

    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);
    glGenVertexArrays(1, &m_vao);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size_bytes(), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size_bytes(), indices.data(), GL_STATIC_DRAW);

    // positions
    Vertex::setVertexAttribPtr();

    m_indexCount = static_cast<unsigned>(indices.size());

    glBindVertexArray(0);
}

void Mesh::draw() const
{
    glBindVertexArray(m_vao);
    glCheckError();
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
    glCheckError();
}