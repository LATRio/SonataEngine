#include "renderer.hpp"

namespace Sonata {

void Renderer::BeginScene()
{
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const std::shared_ptr<VertexArray>& p_VertexArray)
{
    RenderCommand::DrawIndexed(p_VertexArray);
}

}