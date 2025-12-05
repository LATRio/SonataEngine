#pragma once
#include "rendering/renderer_api.hpp"

namespace Sonata {

class OpenGLRendererAPI final : public RendererAPI {
public:
    OpenGLRendererAPI() = default;
    ~OpenGLRendererAPI() override = default;

    void SetClearColor(const glm::vec4& p_Color) const override;
    void Clear() const override;

    void DrawIndexed(const std::shared_ptr<VertexArray>& p_VertexArray) const override;
};

}
