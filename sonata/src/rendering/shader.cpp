#include "shader.hpp"

#include "core.hpp"
#include "opengl/opengl_shader.hpp"
#include "renderer.hpp"

namespace Sonata {

Shader* Shader::Create(const char* vertexPath, const char* fragmentPath)
{
    switch (Renderer::GetAPI())
    {
        case RenderAPI::OpenGL:
            return new OpenGLShader(vertexPath, fragmentPath);
        case RenderAPI::None:
            SN_ASSERT_MSG(false, "RenderAPI::None is not supported");
            return nullptr;
        default:
            SN_ASSERT_MSG(false, "Unknown RenderAPI");
            return nullptr;
    }
}

} // namespace Sonata