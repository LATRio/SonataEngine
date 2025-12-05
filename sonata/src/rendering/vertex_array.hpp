#pragma once

namespace Sonata {

class VertexBuffer;
class IndexBuffer;

class VertexArray {
public:
    virtual ~VertexArray() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& p_VertexBuffer) = 0;
    virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& p_IndexBuffer) = 0;

    static VertexArray* Create();
};

}
