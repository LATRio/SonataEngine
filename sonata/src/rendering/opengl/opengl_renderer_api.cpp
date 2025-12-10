#include "opengl_renderer_api.hpp"

#include "rendering/buffer.hpp"
#include "rendering/vertex_array.hpp"

namespace Sonata {

void OpenGLRendererAPI::Init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLRendererAPI::SetClearColor(const glm::vec4& p_Color) const
{
    glClearColor(p_Color.r, p_Color.g, p_Color.b, p_Color.a);
}

void OpenGLRendererAPI::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& p_VertexArray) const
{
    glDrawElements(GL_TRIANGLES, p_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

}
