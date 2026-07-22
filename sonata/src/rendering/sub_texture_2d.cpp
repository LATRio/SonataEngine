#include "sub_texture_2d.hpp"

namespace Sonata {

SubTexture2D::SubTexture2D(const Ref<Texture2D>& p_Texture, const glm::vec2& p_Min, const glm::vec2& p_Max)
    : m_Texture(p_Texture)
{
    m_TexCoords[0] = {p_Min.x, p_Min.y};
    m_TexCoords[1] = {p_Max.x, p_Min.y};
    m_TexCoords[2] = {p_Max.x, p_Max.y};
    m_TexCoords[3] = {p_Min.x, p_Max.y};
}

Ref<SubTexture2D> SubTexture2D::CreateFromCoords(
    const Ref<Texture2D>& p_Texture, const glm::vec2& p_Coords, const glm::vec2& p_CellSize,
    const glm::vec2& p_SpriteSize)
{
    glm::vec2 min{
        (p_Coords.x * p_CellSize.x) / static_cast<float>(p_Texture->GetWidth()),
        (p_Coords.y * p_CellSize.y) / static_cast<float>(p_Texture->GetHeight())};
    glm::vec2 max{
        ((p_Coords.x + p_SpriteSize.x) * p_CellSize.x) / static_cast<float>(p_Texture->GetWidth()),
        ((p_Coords.y + p_SpriteSize.y) * p_CellSize.y) / static_cast<float>(p_Texture->GetHeight())};
    return CreateRef<SubTexture2D>(p_Texture, min, max);
}

} // namespace Sonata
