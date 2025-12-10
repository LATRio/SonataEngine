#include "shader.hpp"

#include "renderer.hpp"
#include "opengl/opengl_shader.hpp"

namespace Sonata {

Shader* Shader::Create(const char* vertexPath, const char* fragmentPath)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::OpenGL:
            return new OpenGLShader(vertexPath, fragmentPath);
        case RendererAPI::API::None:
            SN_ASSERT_MSG(false, "RenderAPI::None is not supported");
            return nullptr;
        default:
            SN_ASSERT_MSG(false, "Unknown RenderAPI");
            return nullptr;
    }
}

} // namespace Sonata