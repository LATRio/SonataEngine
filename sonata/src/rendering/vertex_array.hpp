#pragma once
#include "core.hpp"

namespace Sonata {

class VertexBuffer;
class IndexBuffer;

class VertexArray {
public:
    virtual ~VertexArray() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(const Ref<VertexBuffer>& p_VertexBuffer) = 0;
    virtual void SetIndexBuffer(const Ref<IndexBuffer>& p_IndexBuffer) = 0;

    [[nodiscard]] virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

    static Ref<VertexArray> Create();
};

} // namespace Sonata
