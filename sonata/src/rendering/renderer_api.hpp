#pragma once
#include "glm_wrapper.hpp"

namespace Sonata {

class VertexArray;

class RendererAPI {
public:
    enum class API
    {
        None = 0,
        OpenGL = 1,
    };
    virtual ~RendererAPI() = default;

    virtual void SetClearColor(const glm::vec4& p_Color) const = 0;
    virtual void Clear() const = 0;

    virtual void DrawIndexed(const std::shared_ptr<VertexArray>& p_VertexArray) const = 0;

    static API GetAPI() { return s_RenderAPI; }

private:
    static API s_RenderAPI;
};

}
