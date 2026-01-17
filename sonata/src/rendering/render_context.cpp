#include "render_context.hpp"

#include "opengl/opengl_context.hpp"
#include "renderer.hpp"

namespace Sonata {

Scope<RenderContext> RenderContext::Create(SDL_Window* p_Window)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::OpenGL:
            return CreateScope<OpenGLContext>(p_Window);
        case RendererAPI::API::Vulkan:
            SN_ASSERT_MSG(false, "Vulkan RenderContext isn't implemented yet!");
            return nullptr;
        case RendererAPI::API::None:
            SN_ASSERT_MSG(false, "RenderAPI::None is not supported");
            return nullptr;
        default:
            SN_ASSERT_MSG(false, "Unknown RenderAPI");
            return nullptr;
    }
}

} // namespace Sonata
