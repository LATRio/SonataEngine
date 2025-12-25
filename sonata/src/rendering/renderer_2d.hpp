#pragma once
#include "core.hpp"
#include "orthographic_camera.hpp"

namespace Sonata {

class Texture2D;

class Renderer2D {
public:
    static void Init();
    static void Shutdown();

    static void BeginScene(const OrthographicCamera& camera);
    static void EndScene();
    static void Flush();
    static void FlushAndReset();

    static void DrawQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color);
    static void DrawQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color);
    static void DrawQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, const Ref<Texture2D>& p_Texture, float p_TilingFactor = 1.0f);
    static void DrawQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, const Ref<Texture2D>& p_Texture, float p_TilingFactor = 1.0f);

    static void DrawRotatedQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, float p_Rotation, const glm::vec4& p_Color);
    static void DrawRotatedQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, float p_Rotation, const glm::vec4& p_Color);
    static void DrawRotatedQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, float p_Rotation, const Ref<Texture2D>& p_Texture, float p_TilingFactor = 1.0f);
    static void DrawRotatedQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, float p_Rotation, const Ref<Texture2D>& p_Texture, float p_TilingFactor = 1.0f);

    static void SetTintColor(const glm::vec4& p_TintColor) { s_TintColor = p_TintColor; }
    static void ResetTintColor() { s_TintColor = glm::vec4(1.0f); }

    struct Statistics
    {
        uint32_t DrawCalls{};
        uint32_t QuadCount{};

        uint32_t GetTotalVertexCount() const { return QuadCount * 4; }
        uint32_t GetTotalIndexCount() const { return QuadCount * 6; }
    };

    static void ResetStats();
    static Statistics GetStats();

private:
    static glm::vec4 s_TintColor;

    static void AddQuad(const glm::mat4& p_Transform, const glm::vec4& p_Color, int32_t p_TexIndex, float p_TilingFactor);
};

} // namespace Sonata
