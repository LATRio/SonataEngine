#include "opengl_buffer.hpp"

namespace Sonata {

////////////////////////
// OpenGLVertexBuffer //
////////////////////////

GLenum TypeToGL(ShaderDataType p_Type)
{
    switch (p_Type)
    {
        case ShaderDataType::Float:
        case ShaderDataType::Float2:
        case ShaderDataType::Float3:
        case ShaderDataType::Float4:    return GL_FLOAT;
        case ShaderDataType::Mat3:      return GL_FLOAT_MAT3;
        case ShaderDataType::Mat4:      return GL_FLOAT_MAT4;
        case ShaderDataType::Int:
        case ShaderDataType::Int2:
        case ShaderDataType::Int3:
        case ShaderDataType::Int4:      return GL_INT;
        case ShaderDataType::Bool:      return GL_BOOL;
        default: SN_ENGINE_ERR("Wrong ShaderDataType: {}", static_cast<int>(p_Type)); return GL_NONE;
    }
}

OpenGLVertexBuffer::OpenGLVertexBuffer(const GLfloat* p_Vertices, const GLsizeiptr p_Size)
{
    glCreateBuffers(1, &m_BufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
    glBufferData(GL_ARRAY_BUFFER, p_Size, p_Vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_BufferID);
}

void OpenGLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}

void OpenGLVertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::Link() const
{
    SN_ASSERT_MSG(m_Layout.GetElements().size(), "Vertex buffer has no layout!");

    size_t index{};
    for (const auto& elem : m_Layout.GetElements())
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index++,
            elem.GetComponentCount(),
            TypeToGL(elem.Type),
            elem.Normalized,
            m_Layout.GetStride(),
            reinterpret_cast<void*>(elem.Offset));
    }
}

///////////////////////
// OpenGLIndexBuffer //
///////////////////////

OpenGLIndexBuffer::OpenGLIndexBuffer(const GLuint* p_Data, const ssize_t p_Count)
    : m_Count(p_Count)
{
    glCreateBuffers(1, &m_BufferID);
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * static_cast<GLsizeiptr>(sizeof(GLuint)), p_Data, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &m_BufferID);
}

void OpenGLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
}

void OpenGLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
int OpenGLIndexBuffer::GetCount() const
{
    return static_cast<int>(m_Count);
}

} // namespace Sonata