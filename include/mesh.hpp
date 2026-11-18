#pragma once

#include <vector>
#include <span>

#include "vertex.hpp"

struct MeshData
{
    std::vector<Vertex> m_vertices;
    std::vector<unsigned> m_indices;
};


class Mesh {
    unsigned m_vao = 0;
    unsigned m_vbo = 0;
    unsigned m_ebo = 0;
    unsigned m_indexCount = 0;  

public:
    Mesh() = default;
    // explicit Mesh(std::span<const Vertex> vertecies, std::span<const unsigned> indicies);
    explicit Mesh(const MeshData& meshData);

    // unsigned vao() const { return m_vao; }
    // unsigned vbo() const { return m_vbo; }
    // unsigned ebo() const { return m_ebo; }
    // unsigned indexCount() const { return m_indexCount; }

    void init(const MeshData& meshData);
    void draw() const;

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    
    ~Mesh();
};