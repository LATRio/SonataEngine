#include "buffer.hpp"

#include "core.hpp"
#include "renderer.hpp"
#include "opengl/opengl_buffer.hpp"

namespace Sonata {

void BufferLayout::CalculateOffsetAndStride()
{
    int offset{};
    for (auto& element : m_Elements)
    {
        element.Offset = offset;
        offset += element.Size;
        m_Stride += element.Size;
    }
}

VertexBuffer* VertexBuffer::Create(const float* p_Vertices, const ssize_t p_Size)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::OpenGL:
        return new OpenGLVertexBuffer(p_Vertices, p_Size);
    case RendererAPI::API::None:
        SN_ASSERT_MSG(false, "RenderAPI::None is not supported");
        return nullptr;
    default:
        SN_ASSERT_MSG(false, "Unknown RenderAPI");
        return nullptr;
    }
}

IndexBuffer* IndexBuffer::Create(const unsigned int* p_Indices, const ssize_t p_Count)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::OpenGL:
        return new OpenGLIndexBuffer(p_Indices, p_Count);
    case RendererAPI::API::None:
        SN_ASSERT_MSG(false, "RenderAPI::None is not supported");
        return nullptr;
    default:
        SN_ASSERT_MSG(false, "Unknown RenderAPI");
        return nullptr;
    }
}

}
