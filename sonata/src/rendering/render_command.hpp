#pragma once
#include "renderer_api.hpp"

namespace Sonata {

class VertexArray;

class RenderCommand {
public:
    static void Init()
    {
        s_RendererAPI->Init();
    }

    static void SetViewport(const int p_X, const int p_Y, const int p_Width, const int p_Height)
    {
        s_RendererAPI->SetViewport(p_X, p_Y, p_Width, p_Height);
    }

    static void SetClearColor(const glm::vec4& p_Color)
    {
        s_RendererAPI->SetClearColor(p_Color);
    }

    static void Clear()
    {
        s_RendererAPI->Clear();
    }

    static void DrawIndexed(const Ref<VertexArray>& p_VertexArray)
    {
        s_RendererAPI->DrawIndexed(p_VertexArray);
    }

private:
    static RendererAPI* s_RendererAPI;
};

}
