#include "opengl_vertexarray.hpp"

#include "rendering/buffer.hpp"

namespace Sonata {

GLenum TypeToGL(ShaderDataType p_Type)
{
    switch (p_Type)
    {
    case ShaderDataType::Float:
    case ShaderDataType::Float2:
    case ShaderDataType::Float3:
    case ShaderDataType::Float4:
    case ShaderDataType::Mat3:
    case ShaderDataType::Mat4:      return GL_FLOAT;
    case ShaderDataType::Int:
    case ShaderDataType::Int2:
    case ShaderDataType::Int3:
    case ShaderDataType::Int4:      return GL_INT;
    case ShaderDataType::Bool:      return GL_BOOL;
    default: SN_ENGINE_ERR("Wrong ShaderDataType: {}", static_cast<int>(p_Type)); return GL_NONE;
    }
}

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
    SN_ASSERT_MSG(!p_VertexBuffer->GetLayout().GetElements().empty(), "Vertex buffer has no layout!");

    p_VertexBuffer->Bind();
    const auto& layout = p_VertexBuffer->GetLayout();
    for (const auto& elem : layout.GetElements())
    {
        switch (elem.Type)
        {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4: {
                glEnableVertexAttribArray(m_VertexBufferIndex);
                glVertexAttribPointer(m_VertexBufferIndex,
                    elem.GetComponentCount(),
                    TypeToGL(elem.Type),
                    elem.Normalized,
                    layout.GetStride(),
                    reinterpret_cast<void*>(elem.Offset));
                m_VertexBufferIndex++;
                break;
            }
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
            case ShaderDataType::Bool: {
                glEnableVertexAttribArray(m_VertexBufferIndex);
                glVertexAttribIPointer(m_VertexBufferIndex,
                    elem.GetComponentCount(),
                    TypeToGL(elem.Type),
                    layout.GetStride(),
                    reinterpret_cast<void*>(elem.Offset));
                m_VertexBufferIndex++;
                break;
            }
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4: {
                const int count = elem.GetComponentCount();
                for (int i = 0; i < count; i++)
                {
                    glEnableVertexAttribArray(m_VertexBufferIndex);
                    glVertexAttribPointer(m_VertexBufferIndex,
                        count,
                        TypeToGL(elem.Type),
                        elem.Normalized,
                        layout.GetStride(),
                        reinterpret_cast<void*>(elem.Offset + static_cast<int>(sizeof(float)) * count * i));
                    glVertexAttribDivisor(m_VertexBufferIndex, 1);
                    m_VertexBufferIndex++;
                }
                break;
            }
            default:
                SN_ENGINE_FATAL("Unknown ShaderDataType: {}", static_cast<int>(elem.Type));
        }
    }

    m_VertexBuffers.push_back(p_VertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& p_IndexBuffer)
{
    Bind();
    p_IndexBuffer->Bind();

    m_IndexBuffer = p_IndexBuffer;
}
const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
{
    return m_IndexBuffer;
}

} // namespace Sonata
