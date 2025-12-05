#pragma once
#include "rendering/vertex_array.hpp"

namespace Sonata {

class OpenGLVertexArray final : public VertexArray {
public:
    OpenGLVertexArray();
    ~OpenGLVertexArray() override;

    void Bind() const override;
    void Unbind() const override;
    void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& p_VertexBuffer) override;
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& p_IndexBuffer) override;

    const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override;

private:
    std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
    GLuint m_ArrayID{};
};

}
