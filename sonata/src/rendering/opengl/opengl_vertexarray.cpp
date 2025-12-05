#include "opengl_vertexarray.hpp"

#include "rendering/buffer.hpp"

namespace Sonata {

OpenGLVertexArray::OpenGLVertexArray()
{
    glCreateVertexArrays(1, &m_ArrayID);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &m_ArrayID);
}

void OpenGLVertexArray::Bind() const
{
    glBindVertexArray(m_ArrayID);
}

void OpenGLVertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& p_VertexBuffer)
{
    Bind();
    p_VertexBuffer->Bind();
    p_VertexBuffer->Link();
    Unbind();
    m_VertexBuffers.push_back(p_VertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& p_IndexBuffer)
{
    Bind();
    p_IndexBuffer->Bind();
    Unbind();
    m_IndexBuffer = p_IndexBuffer;
}

}
