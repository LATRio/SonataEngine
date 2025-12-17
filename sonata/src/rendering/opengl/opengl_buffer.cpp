#include "opengl_buffer.hpp"

#include "profiler/instrumentor.hpp"

namespace Sonata {

////////////////////////
// OpenGLVertexBuffer //
////////////////////////

OpenGLVertexBuffer::OpenGLVertexBuffer(const GLfloat* p_Vertices, const GLsizeiptr p_Size)
{
    SN_PROFILE_FUNCTION();

    glCreateBuffers(1, &m_BufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
    glBufferData(GL_ARRAY_BUFFER, p_Size, p_Vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    SN_PROFILE_FUNCTION();

    glDeleteBuffers(1, &m_BufferID);
}

void OpenGLVertexBuffer::Bind() const
{
    SN_PROFILE_FUNCTION();

    glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}

void OpenGLVertexBuffer::Unbind() const
{
    SN_PROFILE_FUNCTION();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

///////////////////////
// OpenGLIndexBuffer //
///////////////////////

OpenGLIndexBuffer::OpenGLIndexBuffer(const GLuint* p_Data, const ssize_t p_Count)
    : m_Count(p_Count)
{
    SN_PROFILE_FUNCTION();

    glCreateBuffers(1, &m_BufferID);
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * static_cast<GLsizeiptr>(sizeof(GLuint)), p_Data, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    SN_PROFILE_FUNCTION();

    glDeleteBuffers(1, &m_BufferID);
}

void OpenGLIndexBuffer::Bind() const
{
    SN_PROFILE_FUNCTION();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
}

void OpenGLIndexBuffer::Unbind() const
{
    SN_PROFILE_FUNCTION();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} // namespace Sonata
