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
