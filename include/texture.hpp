#pragma once

#include "pch.hpp"

enum class TexUnit
{
    u0 = GL_TEXTURE0,
    u1,  u2,  u3,  u4,  u5,  u6,  u7,  u8,  u9,  u10,
    u11, u12, u13, u14, u15, u16, u17, u18, u19, u20,
    u21, u22, u23, u24, u25, u26, u27, u28, u29, u30,
};

class Texture
{
    unsigned m_id = 0;
    int m_width = 0, m_height = 0;
    int m_channels = 0; // number of channels
    // unsigned char* image = nullptr;
public:
    static void flipVerticallyOnLoad(bool value);

    Texture() = default;
    ~Texture();

    // Texture(Texture&& other) noexcept;
    // Texture& operator=(Texture&& other);

    glm::ivec2 getSize() const { return { m_width, m_height }; }

    void setWrapS(GLenum wrapMode) const;
    void setWrapT(GLenum wrapMode) const;
    void setWrappings(GLenum wrapS, GLenum wrapT) const;

    void setMinFilter(GLenum filter) const;
    void setMagFilter(GLenum filter) const;
    void setFilters(GLenum minFilter, GLenum magFilter) const;

    // void bind() const;
    void bind(TexUnit unit) const;
    void unbind() const;

    bool loadFromFile(std::string_view filepath);
    bool old_loadFromFile(std::string_view filepath);
    void destroy();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
private:
    bool initOpenGLtexture();
};