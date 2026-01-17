#pragma once
#include "core.hpp"
#include "glm_wrapper.hpp"

namespace Sonata {

class VertexArray;

class RendererAPI {
public:
    enum class API
    {
        None = 0,
        OpenGL = 1,
        Vulkan = 2,
    };
    virtual ~RendererAPI() = default;

    virtual void Init() = 0;
    virtual void SetViewport(int p_X, int p_Y, int p_Width, int p_Height) const = 0;
    virtual void SetClearColor(const glm::vec4& p_Color) const = 0;
    virtual void Clear() const = 0;

    virtual void DrawIndexed(const Ref<VertexArray>& p_VertexArray, int32_t p_IndexCount = 0) const = 0;

    static API GetAPI() { return s_RenderAPI; }

private:
    static API s_RenderAPI;
};

} // namespace Sonata
