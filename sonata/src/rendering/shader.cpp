#include "shader.hpp"

#include "renderer.hpp"
#include "opengl/opengl_shader.hpp"

namespace Sonata {

Shader* Shader::Create(const std::string_view p_FilePath)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::OpenGL:
            return new OpenGLShader(p_FilePath);
        case RendererAPI::API::None:
            SN_ASSERT_MSG(false, "RenderAPI::None is not supported");
            return nullptr;
        default:
            SN_ASSERT_MSG(false, "Unknown RenderAPI");
            return nullptr;
    }
}

Shader* Shader::Create(const std::string_view p_VertexPath, const std::string_view p_FragmentPath)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::OpenGL:
            return new OpenGLShader(p_VertexPath, p_FragmentPath);
        case RendererAPI::API::None:
            SN_ASSERT_MSG(false, "RenderAPI::None is not supported");
            return nullptr;
        default:
            SN_ASSERT_MSG(false, "Unknown RenderAPI");
            return nullptr;
    }
}

}
