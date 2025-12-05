#pragma once
#include "render_command.hpp"

namespace Sonata {

class VertexArray;

class Renderer {
public:
    static void BeginScene();
    static void EndScene();

    static void Submit(const std::shared_ptr<VertexArray>& p_VertexArray);

    static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
};

}
