#include "texture.hpp"

#include "opengl/opengl_texture2d.hpp"
#include "renderer.hpp"

namespace Sonata {

Ref<Texture2D> Texture2D::Create(const std::string& p_Path)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLTexture2D>(p_Path);
    case RendererAPI::API::None:
        SN_ASSERT_MSG(false, "RenderAPI::None is not supported");
        return nullptr;
    default:
        SN_ASSERT_MSG(false, "Unknown RenderAPI");
        return nullptr;
    }
}

}
