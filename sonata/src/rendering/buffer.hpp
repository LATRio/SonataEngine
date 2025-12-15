#pragma once
#include "core.hpp"

namespace Sonata {

enum class ShaderDataType
{
    None = 0,
    Float,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4,
    Int,
    Int2,
    Int3,
    Int4,
    Bool,
};

static int ShaderDataTypeSize(const ShaderDataType p_Type)
{
    switch (p_Type)
    {
        case ShaderDataType::Float:     return 4;
        case ShaderDataType::Float2:    return 8;
        case ShaderDataType::Float3:    return 12;
        case ShaderDataType::Float4:    return 16;
        case ShaderDataType::Mat3:      return 36;
        case ShaderDataType::Mat4:      return 64;
        case ShaderDataType::Int:       return 4;
        case ShaderDataType::Int2:      return 8;
        case ShaderDataType::Int3:      return 12;
        case ShaderDataType::Int4:      return 16;
        case ShaderDataType::Bool:      return 1;
        default:                        return 0;
    }

    SN_ASSERT_MSG(false, "Unknown ShaderDataType");
}

struct BufferElement
{
    std::string Name{};
    ShaderDataType Type{};
    int Size{};
    int Offset{};
    bool Normalized{};

    BufferElement(const ShaderDataType p_Type, const std::string_view p_Name, const bool p_Normalized = false)
        : Name(p_Name), Type(p_Type), Size(ShaderDataTypeSize(p_Type)), Normalized(p_Normalized) {}

    [[nodiscard]] uint8_t GetComponentCount() const
    {
        switch (Type)
        {
            case ShaderDataType::Float:     return 1;
            case ShaderDataType::Float2:    return 2;
            case ShaderDataType::Float3:    return 3;
            case ShaderDataType::Float4:    return 4;
            case ShaderDataType::Mat3:      return 9;
            case ShaderDataType::Mat4:      return 16;
            case ShaderDataType::Int:       return 1;
            case ShaderDataType::Int2:      return 2;
            case ShaderDataType::Int3:      return 3;
            case ShaderDataType::Int4:      return 4;
            case ShaderDataType::Bool:      return 1;
            default:                        return 0;
        }
    }
};

class BufferLayout
{
public:
    BufferLayout() = default;
    BufferLayout(const std::initializer_list<BufferElement>& p_Elements)
        : m_Elements(p_Elements)
    {
        CalculateOffsetAndStride();
    }

    [[nodiscard]] int GetStride() const { return m_Stride; }

    [[nodiscard]] const std::vector<BufferElement>& GetElements() const { return m_Elements; }

private:
    std::vector<BufferElement> m_Elements{};
    int m_Stride{};

    void CalculateOffsetAndStride();
};

class VertexBuffer {
public:
    virtual ~VertexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetLayout(const BufferLayout& layout) = 0;
    [[nodiscard]] virtual const BufferLayout& GetLayout() const = 0;

    static Ref<VertexBuffer> Create(const float* p_Vertices, ssize_t p_Size);
};

class IndexBuffer
{
public:
    virtual ~IndexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    [[nodiscard]] virtual int GetCount() const = 0;

    static Ref<IndexBuffer> Create(const unsigned int* p_Indices, ssize_t p_Count);
};

}
