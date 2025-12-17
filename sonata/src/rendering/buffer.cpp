#include "buffer.hpp"

#include "core.hpp"
#include "opengl/opengl_buffer.hpp"
#include "profiler/instrumentor.hpp"
#include "renderer.hpp"

namespace Sonata {

void BufferLayout::CalculateOffsetAndStride()
{
    SN_PROFILE_FUNCTION();

    int offset{};
    for (auto& element : m_Elements)
    {
        element.Offset = offset;
        offset += element.Size;
        m_Stride += element.Size;
    }
}

Ref<VertexBuffer> VertexBuffer::Create(const float* p_Vertices, const ssize_t p_Size)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexBuffer>(p_Vertices, p_Size);
        case RendererAPI::API::None:
            SN_ASSERT_MSG(false, "RenderAPI::None is not supported");
            return nullptr;
        default:
            SN_ASSERT_MSG(false, "Unknown RenderAPI");
            return nullptr;
    }
}

Ref<IndexBuffer> IndexBuffer::Create(const unsigned int* p_Indices, const ssize_t p_Count)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLIndexBuffer>(p_Indices, p_Count);
        case RendererAPI::API::None:
            SN_ASSERT_MSG(false, "RenderAPI::None is not supported");
            return nullptr;
        default:
            SN_ASSERT_MSG(false, "Unknown RenderAPI");
            return nullptr;
    }
}

} // namespace Sonata
