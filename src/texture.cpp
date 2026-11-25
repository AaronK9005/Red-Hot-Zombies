#include "texture.hpp"

#include "stb_image.h"

Texture::~Texture()
{
  if (m_id)
  {
    glDeleteTextures(1, &m_id);
  }
}

// Texture::Texture(std::string_view filepath)
// {
//     loadFromFile(filepath);
// }

Texture::Texture(Texture&& other) noexcept
  : m_id(std::exchange(other.m_id, 0)),
    m_width(std::exchange(other.m_width, 0)),
    m_height(std::exchange(other.m_height, 0)) {}

Texture& Texture::operator=(Texture&& other) {
    //!
    return other;
}

bool Texture::loadFromFile(std::string_view filepath)
{
  if (filepath.empty()) return false;

  unsigned char *data = stbi_load(filepath.data(), &m_width, &m_height, &m_channels, 0);
  if (!data)
  {
    return false;
  }

  //? do i need dynamic internalFormat depending on number of channels?
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

  stbi_image_free(data);

  return true;
}

bool Texture::initOpenGLtexture()
{
  glGenTextures(1, &m_id);
  if (m_id == 0)
  {
    return false;
  }

  return true;
}

void Texture::bind() const
{
  glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind() const
{
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::generateMipmaps() const
{
  glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::destroy()
{
  if (m_id)
  {
    glDeleteTextures(1, &m_id);
  }

  m_id = 0;
  m_width = 0;
  m_height = 0;
  m_channels = 0;
}

void Texture::setWrapS(GLenum wrapMode) const
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
}

void Texture::setWrapT(GLenum wrapMode) const
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
}

void Texture::setWrappings(GLenum wrapS, GLenum wrapT) const
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
}


void Texture::setMinFilter(GLenum filter) const
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
}

void Texture::setMagFilter(GLenum filter) const
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
}

void Texture::setFilters(GLenum minFilter, GLenum magFilter) const
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

