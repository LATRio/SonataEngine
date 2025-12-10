#pragma once
#include "rendering/texture.hpp"

namespace Sonata {

class OpenGLTexture2D final : public Texture2D {
public:
    explicit OpenGLTexture2D(const std::string& p_Path);
    ~OpenGLTexture2D() override;

    [[nodiscard]] int GetWidth() const override { return m_Width; }
    [[nodiscard]] int GetHeight() const override { return m_Height; }

    void Bind(uint32_t p_Unit = 0) const override;

private:
    std::string m_Path;

    int m_Width{};
    int m_Height{};

    GLuint m_TextureID{};
};

}
