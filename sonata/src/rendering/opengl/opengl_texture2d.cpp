#include "opengl_texture2d.hpp"

namespace Sonata {

OpenGLTexture2D::OpenGLTexture2D(const std::string_view p_Path)
    : m_Path(p_Path)
{
    int channels;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc* data{stbi_load(m_Path.c_str(), &m_Width, &m_Height, &channels, 0)};
    SN_ASSERT_MSG(data, std::format("Failed to load texture from \"{}\"", m_Path));

    GLenum internalFormat{};
    GLenum dataFormat{};
    if (channels == 4)
    {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
    }
    else if (channels == 3)
    {
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    }

    glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
    glTextureStorage2D(m_TextureID, 1, internalFormat, m_Width, m_Height);

    glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D()
{
    glDeleteTextures(1, &m_TextureID);
}

void OpenGLTexture2D::Bind(const uint32_t p_Unit) const
{
    glBindTextureUnit(p_Unit, m_TextureID);
}

}