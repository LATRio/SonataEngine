#pragma once
#include "rendering/renderer_api.hpp"

namespace Sonata {

class OpenGLRendererAPI final : public RendererAPI {
public:
    OpenGLRendererAPI() = default;
    ~OpenGLRendererAPI() override = default;

    void Init() override;
    void SetViewport(int p_X, int p_Y, int p_Width, int p_Height) const override;
    void SetClearColor(const glm::vec4& p_Color) const override;
    void Clear() const override;

    void DrawIndexed(const Ref<VertexArray>& p_VertexArray) const override;
};

}
