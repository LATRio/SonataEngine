#include "texture.hpp"

#include "opengl/opengl_texture2d.hpp"
#include "renderer.hpp"

namespace Sonata {

Ref<Texture2D> Texture2D::Create(int p_Width, int p_Height)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLTexture2D>(p_Width, p_Height);
        case RendererAPI::API::None:
            SN_ASSERT_MSG(false, "RenderAPI::None is not supported");
            return nullptr;
        default:
            SN_ASSERT_MSG(false, "Unknown RenderAPI");
            return nullptr;
    }
}

Ref<Texture2D> Texture2D::Create(const std::string_view p_Path)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLTexture2D>(p_Path);
        case RendererAPI::API::None:
            SN_ASSERT_MSG(false, "RenderAPI::None is not supported");
            return nullptr;
        default:
            SN_ASSERT_MSG(false, "Unknown RenderAPI");
            return nullptr;
    }
}

} // namespace Sonata
