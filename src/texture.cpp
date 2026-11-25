#include "texture.hpp"

#include "stb_image.h"
#include "platform/debug.hpp"

Texture::~Texture()
{
  if (m_id)
  {
    glDeleteTextures(1, &m_id);
  }
}

// Texture::Texture(Texture&& other) noexcept
//   : m_id(std::exchange(other.m_id, 0)),
//     m_width(std::exchange(other.m_width, 0)),
//     m_height(std::exchange(other.m_height, 0)) {}

// Texture& Texture::operator=(Texture&& other) {
//     //!
//     return other;
// }

void Texture::flipVerticallyOnLoad(bool value)
{
  stbi_set_flip_vertically_on_load(value);
}

bool Texture::loadFromFile(std::string_view filepath)
{
    if (filepath.empty())
        return false;

    std::string path(filepath);

    int width = 0;
    int height = 0;
    int channels = 0;

    // Always produce RGB output.
    unsigned char* data = stbi_load(
        path.c_str(),
        &width,
        &height,
        &channels,
        STBI_rgb
    );

    if (!data)
        return false;

    if (!initOpenGLtexture())
    {
        stbi_image_free(data);
        return false;
    }

    // Remember previous OpenGL state.
    GLint previousTexture = 0;
    GLint previousAlignment = 4;

    glGetIntegerv(GL_TEXTURE_BINDING_2D, &previousTexture);
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &previousAlignment);

    glBindTexture(GL_TEXTURE_2D, m_id);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB8,
        width,
        height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        data
    );

    // Default texture parameters.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    // Restore previous OpenGL state.
    glPixelStorei(GL_UNPACK_ALIGNMENT, previousAlignment);
    glBindTexture(GL_TEXTURE_2D, previousTexture);

    stbi_image_free(data);

    m_width = width;
    m_height = height;
    m_channels = channels;

    return true;
}

bool Texture::old_loadFromFile(std::string_view filepath)
{
  if (filepath.empty()) return false;

  if (!initOpenGLtexture()) return false;

  unsigned char *data = stbi_load(filepath.data(), &m_width, &m_height, &m_channels, STBI_rgb);
  if (!data)
  {
    destroy();
    return false;
  }

  glBindTexture(GL_TEXTURE_2D, m_id);

  //? do i need dynamic internalFormat depending on number of channels?
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glCheckError();

  stbi_image_free(data);

  return true;
}

bool Texture::initOpenGLtexture()
{
  if (m_id) return true;

  glGenTextures(1, &m_id);
  if (m_id == 0)
  {
    return false;
  }

  return true;
}

// void Texture::bind() const
// {
//   glActiveTexture();
//   glBindTexture(GL_TEXTURE_2D, m_id);
// }

void Texture::bind(TexUnit unit) const
{
  glActiveTexture(static_cast<int>(unit));
  glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind() const
{
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::destroy()
{
  if (m_id)
  {
    glDeleteTextures(1, &m_id);
  }

  m_id = 0;
  // m_width = 0;
  // m_height = 0;
  // m_channels = 0;
}

void Texture::setWrapS(GLenum wrapMode) const
{
  glBindTexture(GL_TEXTURE_2D, m_id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
}

void Texture::setWrapT(GLenum wrapMode) const
{
  glBindTexture(GL_TEXTURE_2D, m_id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
}

void Texture::setWrappings(GLenum wrapS, GLenum wrapT) const
{
  glBindTexture(GL_TEXTURE_2D, m_id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
}

void Texture::setMinFilter(GLenum filter) const
{
  glBindTexture(GL_TEXTURE_2D, m_id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
}

void Texture::setMagFilter(GLenum filter) const
{
  glBindTexture(GL_TEXTURE_2D, m_id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
}

void Texture::setFilters(GLenum minFilter, GLenum magFilter) const
{
  glBindTexture(GL_TEXTURE_2D, m_id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

