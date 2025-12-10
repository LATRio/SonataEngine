#pragma once
#include "rendering/vertex_array.hpp"

namespace Sonata {

class OpenGLVertexArray final : public VertexArray {
public:
    OpenGLVertexArray();
    ~OpenGLVertexArray() override;

    void Bind() const override;
    void Unbind() const override;
    void AddVertexBuffer(const Ref<VertexBuffer>& p_VertexBuffer) override;
    void SetIndexBuffer(const Ref<IndexBuffer>& p_IndexBuffer) override;

    [[nodiscard]] const Ref<IndexBuffer>& GetIndexBuffer() const override;

private:
    std::vector<Ref<VertexBuffer>> m_VertexBuffers;
    Ref<IndexBuffer> m_IndexBuffer;
    GLuint m_ArrayID{};
    GLuint m_VertexBufferIndex{};
};

}
