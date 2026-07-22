#pragma once
#include "glm_wrapper.hpp"
#include "texture.hpp"

namespace Sonata {

class SubTexture2D {
public:
    SubTexture2D(const Ref<Texture2D>& p_Texture, const glm::vec2& p_Min, const glm::vec2& p_Max);

    [[nodiscard]] const Ref<Texture2D>& GetTexture() const { return m_Texture; }
    [[nodiscard]] const glm::vec2* GetTexCoords() const { return m_TexCoords; }

    static Ref<SubTexture2D> CreateFromCoords(
        const Ref<Texture2D>& p_Texture, const glm::vec2& p_Coords, const glm::vec2& p_CellSize,
        const glm::vec2& p_SpriteSize = {1.0f, 1.0f});

private:
    Ref<Texture2D> m_Texture{};

    glm::vec2 m_TexCoords[4]{};
};

} // namespace Sonata
