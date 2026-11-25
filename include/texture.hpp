#pragma once

#include "pch.hpp"

class Texture
{
    unsigned m_id = 0;
    int m_width = 0, m_height = 0;
    int m_channels = 0; // number of channels
    // unsigned char* image = nullptr;
public:
    Texture() = default;
    ~Texture();

    // Texture(std::string_view filepath);

    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other);

    void setWrapS(GLenum wrapMode) const;
    void setWrapT(GLenum wrapMode) const;
    void setWrappings(GLenum wrapS, GLenum wrapT) const;

    void setMinFilter(GLenum filter) const;
    void setMagFilter(GLenum filter) const;
    void setFilters(GLenum minFilter, GLenum magFilter) const;

    void bind() const;
    void unbind() const;

    bool loadFromFile(std::string_view filepath);
    void generateMipmaps() const;
    void destroy();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
private:
    bool initOpenGLtexture();
};