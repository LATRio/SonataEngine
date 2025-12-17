#pragma once
#include <glad/gl.h>

#include "rendering/buffer.hpp"

namespace Sonata {

class OpenGLVertexBuffer final : public VertexBuffer {
public:
    OpenGLVertexBuffer(const GLfloat* p_Vertices, GLsizeiptr p_Size);
    ~OpenGLVertexBuffer() override;

    void Bind() const override;
    void Unbind() const override;

    void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
    [[nodiscard]] const BufferLayout& GetLayout() const override { return m_Layout; }

private:
    GLuint m_BufferID{};
    BufferLayout m_Layout{};
};

class OpenGLIndexBuffer final : public IndexBuffer {
public:
    OpenGLIndexBuffer(const GLuint* p_Data, ssize_t p_Count);
    ~OpenGLIndexBuffer() override;

    void Bind() const override;
    void Unbind() const override;

    [[nodiscard]] int GetCount() const override { return static_cast<int>(m_Count); }

private:
    GLuint m_BufferID{};
    ssize_t m_Count{};
};

} // namespace Sonata
