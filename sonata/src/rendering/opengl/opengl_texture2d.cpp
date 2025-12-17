#include "opengl_texture2d.hpp"

#include "profiler/instrumentor.hpp"

namespace Sonata {

OpenGLTexture2D::OpenGLTexture2D(const std::string_view p_Path) : m_Path(p_Path)
{
    SN_PROFILE_FUNCTION();

    int channels;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc* data{stbi_load(m_Path.c_str(), &m_Width, &m_Height, &channels, 0)};
    SN_ASSERT_MSG(data, std::format("Failed to load texture from \"{}\"", m_Path));

    if (channels == 4)
    {
        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;
    }
    else if (channels == 3)
    {
        m_InternalFormat = GL_RGB8;
        m_DataFormat = GL_RGB;
    }

    SetData(data, m_Width * m_Height * channels);

    stbi_image_free(data);
}

OpenGLTexture2D::OpenGLTexture2D(const int p_Width, const int p_Height)
    : m_Width(p_Width), m_Height(p_Height), m_InternalFormat(GL_RGBA8), m_DataFormat(GL_RGBA) {}

OpenGLTexture2D::~OpenGLTexture2D()
{
    SN_PROFILE_FUNCTION();

    glDeleteTextures(1, &m_TextureID);
}

void OpenGLTexture2D::SetData(const void* p_Data, const int p_Size)
{
    SN_PROFILE_FUNCTION();

    // ReSharper disable once CppDFAConstantConditions
    const int bpp{m_DataFormat == GL_RGBA ? 4 : 3};
    SN_ASSERT_MSG(p_Size == m_Width * m_Height * bpp, "Data must be entire texture!");

    glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
    glTextureStorage2D(m_TextureID, 1, m_InternalFormat, m_Width, m_Height);

    glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, p_Data);
}

void OpenGLTexture2D::Bind(const uint32_t p_Unit) const
{
    SN_PROFILE_FUNCTION();

    glBindTextureUnit(p_Unit, m_TextureID);
}

}