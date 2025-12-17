#pragma once
#include "rendering/texture.hpp"

namespace Sonata {

class OpenGLTexture2D final : public Texture2D {
public:
    explicit OpenGLTexture2D(std::string_view p_Path);
    OpenGLTexture2D(const int p_Width, const int p_Height)
        : m_Width(p_Width)
        , m_Height(p_Height)
        , m_InternalFormat(GL_RGBA8)
        , m_DataFormat(GL_RGBA)
    {}
    ~OpenGLTexture2D() override;

    [[nodiscard]] int GetWidth() const override { return m_Width; }
    [[nodiscard]] int GetHeight() const override { return m_Height; }

    void SetData(const void* p_Data, int p_Size) override;

    void Bind(uint32_t p_Unit) const override;

private:
    std::string m_Path;

    int m_Width{};
    int m_Height{};

    GLuint m_TextureID{};
    GLenum m_InternalFormat{};
    GLenum m_DataFormat{};
};

} // namespace Sonata
