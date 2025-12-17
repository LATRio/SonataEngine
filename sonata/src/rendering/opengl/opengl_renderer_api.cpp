#include "opengl_renderer_api.hpp"

#include "profiler/instrumentor.hpp"
#include "rendering/buffer.hpp"
#include "rendering/vertex_array.hpp"

namespace Sonata {

void OpenGLRendererAPI::Init()
{
    SN_PROFILE_FUNCTION();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
}

void OpenGLRendererAPI::SetViewport(const int p_X, const int p_Y, const int p_Width, const int p_Height) const
{
    SN_PROFILE_FUNCTION();

    SN_ENGINE_INFO("Viewport is being set to {}x{}", p_Width, p_Height);
    glViewport(0, 0, p_Width, p_Height);
}

void OpenGLRendererAPI::SetClearColor(const glm::vec4& p_Color) const
{
    SN_PROFILE_FUNCTION();

    glClearColor(p_Color.r, p_Color.g, p_Color.b, p_Color.a);
}

void OpenGLRendererAPI::Clear() const
{
    SN_PROFILE_FUNCTION();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& p_VertexArray) const
{
    SN_PROFILE_FUNCTION();

    glDrawElements(GL_TRIANGLES, p_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace Sonata
