#include "vertex_array.hpp"

#include "buffer.hpp"
#include "renderer.hpp"
#include "opengl/opengl_vertexarray.hpp"

namespace Sonata {

Ref<VertexArray> VertexArray::Create()
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexArray>();
        case RendererAPI::API::None:
            SN_ASSERT_MSG(false, "RenderAPI::None is not supported");
            return nullptr;
        default:
            SN_ASSERT_MSG(false, "Unknown RenderAPI");
            return nullptr;
    }
}

}