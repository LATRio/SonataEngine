#include "vertex_array.hpp"

#include "renderer.hpp"
#include "buffer.hpp"
#include "opengl/opengl_vertexarray.hpp"

namespace Sonata {

VertexArray* VertexArray::Create()
{
    switch (Renderer::GetAPI())
    {
        case RenderAPI::OpenGL:
            return new OpenGLVertexArray();
        case RenderAPI::None:
            SN_ASSERT_MSG(false, "RenderAPI::None is not supported");
            return nullptr;
        default:
            SN_ASSERT_MSG(false, "Unknown RenderAPI");
            return nullptr;
    }
}

}